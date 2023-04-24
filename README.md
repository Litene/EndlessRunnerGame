The overall project is quite small where a handful of scripts are responsible for how the game works, the SpawnManager script is doing the generation, 
for example, which is a big part of the game. The algorithm for moving the is based on the difficulty, which has a threshold for max movement speed.  
The chance of spawning projectiles is also based on difficulty, which has a very low percent chance in the beginning and a 100% chance with every spawned block after a set amount of time. The difficulty of the game increments at a set pace. Utilizing managers helps keep the code organized and neat, which helps both when writing, and when reading code. A few things were done in the interest of learning rather than being the most efficient.    
  
  
Examples of effective C++ use:   
* Repurposing the third-person controller instead of reinventing the wheel.  
* Having managers responsible for the generation.  
* Responsible for their defining their own behaviors is an example of object-oriented design.   
* Data containers for ease of use, this was utilized by the difficulty.  

