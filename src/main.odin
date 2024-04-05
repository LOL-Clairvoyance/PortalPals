package game

import "core:fmt"
import "vendor:raylib"

SCREEN_WIDTH  :: 800;
SCREEN_HEIGHT :: 450;
PLAYER_SPEED :: 5;

main :: proc() {
    raylib.InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal Pals");
    raylib.SetTargetFPS(60)
    player: Player
    player.Position = raylib.Vector2 { SCREEN_WIDTH / 2, SCREEN_HEIGHT /2 }

    for !raylib.WindowShouldClose() {
        raylib.BeginDrawing()
        raylib.ClearBackground(raylib.RAYWHITE);  
        raylib.DrawCircleV(player.Position, 20, raylib.RED)
        raylib.DrawText("Use ZQSD to move", 10, 10, 20, raylib.DARKGRAY);
        player_move(&player);
        player_attack(&player);
        raylib.EndDrawing()
    }

    raylib.CloseWindow()
}
