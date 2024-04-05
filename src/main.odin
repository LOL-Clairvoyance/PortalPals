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
    player.Health = 3;
    player.Portal_Cleared = 0;

    for !raylib.WindowShouldClose() {
        raylib.BeginDrawing()
        raylib.ClearBackground(raylib.RAYWHITE);  
        player_draw(&player);
        player_draw_quest(&player);
        player_draw_health(&player);
        player_update(&player);
        raylib.EndDrawing()
    }

    raylib.CloseWindow()
}
