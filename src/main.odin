package game

import "core:fmt"
import "vendor:raylib"

SCREEN_WIDTH  :: 800;
SCREEN_HEIGHT :: 450;

main :: proc() {
    raylib.InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Portal pals");

    for !raylib.WindowShouldClose() {
        raylib.BeginDrawing()

        raylib.ClearBackground(raylib.RAYWHITE);
        raylib.DrawText("Raylib!!", 190, 200, 20, raylib.BLACK);

        raylib.EndDrawing()
    }

    raylib.CloseWindow()
}
