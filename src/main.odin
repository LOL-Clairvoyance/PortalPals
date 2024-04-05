package game

import "core:fmt"
import "vendor:raylib"
import "core:strings"

SCREEN_WIDTH  :: 800;
SCREEN_HEIGHT :: 450;
PLAYER_SPEED :: 5;

main :: proc() {
    raylib.InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal Pals");
    raylib.SetTargetFPS(60)
    player: Player
    player.Position = raylib.Vector2 { SCREEN_WIDTH / 2, SCREEN_HEIGHT /2 }
    player

    for !raylib.WindowShouldClose() {
        raylib.BeginDrawing()
        raylib.ClearBackground(raylib.RAYWHITE);  
        raylib.DrawCircleV(player.Position, 20, raylib.RED)
        quest := fmt.aprintf("Find and Clear %i portals!", 5 - Portal_Cleared);
        raylib.DrawText(strings.unsafe_string_to_cstring(quest), 10, 10, 20, raylib.DARKGRAY);
        player_update(&player);
        raylib.EndDrawing()
    }

    raylib.CloseWindow()
}
