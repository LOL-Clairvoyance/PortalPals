package game

import "core:fmt"
import "vendor:raylib"
import "core:strings"

Player :: struct {
    Position: raylib.Vector2,
    Health: int,
    Portal_Cleared: int
}

player_move :: proc (player : ^Player) 
{
    if raylib.IsKeyDown(raylib.KeyboardKey.A) {
        player.Position[0] -= PLAYER_SPEED
    }
    if raylib.IsKeyDown(raylib.KeyboardKey.D) {
        player.Position[0] += PLAYER_SPEED
    }
    if raylib.IsKeyDown(raylib.KeyboardKey.W) {
        player.Position[1] -= PLAYER_SPEED
    }
    if raylib.IsKeyDown(raylib.KeyboardKey.S) {
        player.Position[1] += PLAYER_SPEED
    }
}

player_attack :: proc (player : ^Player)
{
    if raylib.IsMouseButtonPressed(raylib.MouseButton.LEFT) 
    {
        mousePos := raylib.GetMousePosition()
        attackDirection := raylib.Vector2{mousePos[0]-player.Position[0], mousePos[1]-player.Position[1]}

        if abs(attackDirection[0]) > abs(attackDirection[1]) {
            if attackDirection[0] > 0 {
                fmt.println("Attacking right")
            } else {
                fmt.println("Attacking left")
            }
        } else {
            if attackDirection[1] > 0 {
                fmt.println("Attacking down")
            } else {
                fmt.println("Attacking up")
            }
        }
    }
}

player_draw_health :: proc (player : ^Player)
{
    for i := 1; i < player.Health + 1; i += 1 {
        raylib.DrawCircleV({20 * f32(i), 20}, 10, raylib.RED)
    }
}

player_draw_quest :: proc (player : ^Player)
{
    quest := fmt.aprintf("Find and Clear %i portals!", 5 - player.Portal_Cleared);
    raylib.DrawText(strings.unsafe_string_to_cstring(quest), 10, SCREEN_HEIGHT - 50, 20, raylib.DARKGRAY);
}

player_draw :: proc (player : ^Player)
{
    raylib.DrawCircleV(player.Position, 20, raylib.BLUE);
}

player_update :: proc (player : ^Player)
{
    player_move(player);
    player_attack(player);
}