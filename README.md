# Unreal Runner

An enless runner made in unreal using primarily c++ to make stuff function for an assignment for a course in FutureGames Programming.

I've honestly had some major issues regarding starting work with UE5, didn't really get stuff working at all untill 24/4 basically. 
wich also happens to be the deadline for the first part of the assignment.

## What's there for part 1
So far i got a basic spherical character moving and some blocks spawning, that then move in the direction of the player. set up a static camera so you can see properly and set it up so that it's a variable playfield.

## What's new for part 2
I Made the spawner a singleton so that it could hold global settings and handle the scores, could have done the scores seperatley, but felt easier to work in the same script as when i add new ones unreal keeps getting confused.
The spawner also handles the moving platforms through their entire lifecycle, reusing the ones that has already passed the player so it object pools properly.
I got the spawner handeling a score that's constant over time and i got the player counting down lives and reporting damage and hit to remove actors aswell as tell the spawner when it's dead so it knows to stop the game and open a game over menu.
We got the option added to make a bot rather than a second player so i broke out the controlling functions and got them working seperatley with the same base.
I added so that if you're within a scertain distance from the object you're dodging it reports it to the spawner that then removes one of the moving platforms, one of the more freshly spawned ones.
I experimented with ui and got a hud running so you can see your score on screen througout play.

I'm not really sure what kind of bugs i've encountered or how i've solved them. i kind of forgot througout the assignment. but i did struggle a few times with unreal loosing my scripts entierly. but that was cause i had to apparenly build in multiple ways.
And sorry for the lack of comments, i get a bit lazy with those when i'm stressed and claim it's to help me practice making and reading code effectivley.

