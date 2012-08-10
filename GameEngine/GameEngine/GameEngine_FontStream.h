// GameEngine_FontStream.h
//
// Author: John Conder
// Date: 07/09/2012
//
// Purpose:
// Provides a FontStream object that can be used to pass variable data to the
// GameEngine_Font engine instead of textual strings.  The reasoning behind
// this is in order to provide a way to display things such as Frames Per 
// Second (FPS) which change constantly, and should be updated every frame,
// without having to resort to manually calling a Print() for each update.
// Instead, you pass the string "FPS: " and a pointer to the FPS value
// to a FontStream, and then Print the fontstream on a FontEngine.

#pragma once

class GameEngine_FontStream
{
};