# Geometry-Wars-main

This project is inspired from [Catalina430's Geometry Wars](https://github.com/Catalina430/Geometry-Wars) where Catalina430 created a game analogous to the top-down multi-directional shoot 'em up [Geometry Wars](https://en.wikipedia.org/wiki/Geometry_Wars).
The purpose of this project is to amalgamate SFML with ImGui.
I could not find Catalina430's contact information through which I could apprise them of my intention to ameliorate their project, so I assumed their approbation, for downloading their project and adulterating it with my code, from their repository being public.

Almost all the SFML part of this project was written by Catalina430 and I appreciate the scintillating details of the graphics from this SFML part; for example:
- The alpha of a bullet abates in every frame till it is no longer active.
- Holding your shooting in abeyance, being benighted about the spawn interval of enemies, will cause unchecked growth of enemies - you will see a raft of them. The game will become involved since the window will be inundated with enemies.
- The score on the top-left to galvanize the player.

The changes I made are:
- include GUIs such as tabs, checkboxes, sliders, buttons and collapsing headers
  - Unchecking a checkbox will hold the corresponding part of the system in abeyance.
  - Sliders let you stem the spawing of enemies.
- make spinning of entities independent of movement
