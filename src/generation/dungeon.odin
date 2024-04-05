package generation

import "core:math/rand"
import "core:time"

MAX_WIDTH :: 101
MAX_HEIGHT :: 101
MAX_ROOMS :: 128

ROOM_MIN_SIZE :: 6
ROOM_MAX_SIZE :: 15

Tile :: enum {
    Walkable,
    Solid,
    Stairs
}

Room :: struct {
    x1: i32,
    x2: i32,
    y1: i32,
    y2: i32
}

Map :: struct {
    generated: bool,
    width: i32,
    height: i32,
    array: [MAX_WIDTH][MAX_HEIGHT]Tile,
    rooms: [MAX_ROOMS]Room
}

room_init :: proc(xpos: i32, ypos: i32, width: i32, height: i32) -> Room {
    result: Room
    result.x1 = xpos
    result.y1 = ypos
    result.x2 = xpos + width
    result.y2 = ypos + height
    return result
}

room_center :: proc(room: ^Room) -> (f32, f32) {
    centerX := f32((room.x1 + room.x2) / 2.0)
    centerY := f32((room.y1 + room.y2) / 2.0)
    return centerX, centerY
}

room_intersects :: proc(room: ^Room, other: ^Room) -> bool {
    return (room.x1 <= other.x2 && room.x2 >= other.x1 && room.y1 <= other.y2 && room.y2 >= other.y1)
}

map_generate :: proc(width: i32, height: i32) -> Map {
    result: Map
    result.width = width
    result.height = height

    rand.set_global_seed(u64(time.tick_now()._nsec))
    
    for i in 0..=width {
        for j in 0..=height {
            result.array[i][j] = Tile.Solid;
        }
    }
    num_rooms := 0

    for r in 0..=MAX_ROOMS {
        w := rand.int31_max(ROOM_MAX_SIZE) + ROOM_MIN_SIZE
        h := rand.int31_max(ROOM_MAX_SIZE) + ROOM_MIN_SIZE
        x := rand.int31_max(width - w)
        y := rand.int31_max(height - h)
        
        room := room_init(x, y, w, h)
        failed := false
        for i in 0..=num_rooms {
            if room_intersects(&room, &result.rooms[i]) {
                failed = true
                break
            }
        }

        if !failed {
            create_room(&result, &room);
        
            new_center_x, new_center_y := room_center(&room);
            if num_rooms != 0 {
                prev_x, prev_y := room_center(&result.rooms[num_rooms - 1]);

                if rand.choice([]bool{ true, false }) {
                    create_hor_tunnel(&result, int(prev_x), int(new_center_x), int(prev_y))
                    create_vir_tunnel(&result, int(prev_y), int(new_center_y), int(new_center_x))
                } else {
                    create_vir_tunnel(&result, int(prev_y), int(new_center_y), int(prev_x))
                    create_hor_tunnel(&result, int(prev_x), int(new_center_x), int(new_center_y))
                }
            }

            result.rooms[num_rooms] = room
            num_rooms += 1
        }
    }

    return result
}

@(private)
create_room :: proc(mp: ^Map, room: ^Room) {
    for x := room.x1; x < room.x2; x += 1 {
        for y := room.y1; y < room.y2; y += 1 {
            mp.array[x][y] = Tile.Walkable;
        }
    }
}

@(private)
create_hor_tunnel :: proc(mp: ^Map, x1: int, x2: int, y: int) {
    for x := min(x1, x2); x < max(x1, x2) + 1; x += 1 {
        mp.array[x][y] = Tile.Walkable
    }
}

@(private)
create_vir_tunnel :: proc(mp: ^Map, y1: int, y2: int, x: int) {
    for y := min(y1, y2); y < max(y1, y2) + 1; y += 1 {
        mp.array[x][y] = Tile.Walkable
    }
}
