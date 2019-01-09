For (debian-based)linux, built with C++ and the SDL2 graphics library.

Get dependencies: 
```sh
sudo apt-get -y install g++ libsdl2-dev libsdl2-ttf-dev
```

Get code: 
```sh
git clone https://github.com/plewh/FlappyBird.git
```

Compile: 
```sh
make flap
```

Run: 
```sh
./flap
```

---

TODO:

* Pipes
	* Pipe spawner
	* Pipe entity
	* Pipe graphical assets
* Collision handling
* Scoring
	* Scoring logic
	* Draw score on hud
* Sounds
	* Create sound system
	* Get sound assets
	* Extend event system to include sound triggers
* Polish
	* Hover state at game start
	* Menu scene
		* Initial menu describing controls at game start
		* Pause screen
		* Quit/Restart menu
	* Tweak flappy params to get as close to real game as possible
