package game

import "core:fmt"
import "vendor:raylib"

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

player_update :: proc (player : ^Player)
{
    player_move(player);
    player_attack(player);
}