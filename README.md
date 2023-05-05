The overall project is quite small where a handful of scripts are responsible for how the game works, the SpawnManager script is doing the generation, 
for example, which is a big part of the game. The algorithm for moving the is based on the difficulty, which has a threshold for max movement speed.
The chance of spawning projectiles is also based on difficulty, which has a very low percent chance in the beginning and a 100% chance with every spawned block after a set amount of time. The difficulty of the game increments at a set pace. Utilizing managers helps keep the code organized and neat, which helps both when writing, and when reading code. A few things were done in the interest of learning rather than being the most efficient.    
  
  
Examples of effective C++ use:   
* Repurposing the third-person controller instead of reinventing the wheel.  
* Having managers responsible for the generation.  
* Objects are responsible for their defining their own behaviors is an example of object-oriented design.   
* Data containers for ease of use, this was utilized by the difficulty.  
  

2nd turnin.

Improvements:  
Added all required functionality and rather than going back to refactor the old code I instead opted to learn from what I did and used better practices for all added scripts. I therefore created smaller classes to have a more structured appraoch for part two. I made managers for UI, Save, and So on to keep things neat and organized. 


Complications:
Due to unknown circumstances I wasn't able to make a functioning build, the game works fully in editor but not at all when built, Not even close. After debugging for several hours Im not even closer to understanding why there are so extreme differences in the build (Packaged content).
The issues with build are as following: The game lags like crazy, and crashes after just a short duration when played (just says fatal error and nothing more), the players spawn in incorrect positions and doesn't even keep to their lanes. Also I haven't been able to tell if score functionality works becuase that shows when both players die and the game crashes before that. 


Git commits:
I worked on the same machine for the entire project and therefore only commited once. I know this is bad practice.

Overall:
I hope that this isn't a dealbreaker, I have looked at the criteria and I think that I have shown in my code that I interstand how to build a game utilizing c++.
