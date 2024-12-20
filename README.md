# Zaun: Battle of Nations

## 1. Quick Overview

**Zaun: Battle of Nations** is a shoot'em up (shmup) inspired by the universe of *Arcane* and *League of Legends*. Developed in 3 weeks as part of a student project, this game allows players to control a character from Zaun and engage in battle against the Pacifiers, the main enemies. The goal is to progress through the levels, defeat enemies and bosses, all while exploring a colorful and detailed pixel art world.

The game features a progression system with unique abilities for each character and engaging gameplay mechanics, ranging from automatic shooting to special abilities with various effects. Although the game is not finished, it already offers an immersive experience for fans of the *League of Legends* universe.

- Created in 3 weeks by 2 people.

## 2. Features Implemented

### 2.1. Gameplay

The player can currently control **Ekko** (the only character developed so far) and navigate through an automatic horizontal scrolling environment. The player must:
- **Avoid enemy projectiles**
- **Defeat enemies** of different types (light, medium, advanced)
- **Defeat Marcus (Boss)** to complete level 1 (only level implemented so far)

### 2.2. Character Abilities

Currently, Ekko is the only playable character with the following abilities:
- **Magic Staff (Ability 1)**: Fires a magic boomerang that returns to the player.
- **Slow Zone (Ability 2)**: Creates a zone that slows down enemy fire speed by 5 times.
- **Dash (Ability 3)**: A short-distance rapid movement.
- **Ultimate**: Becomes invincible.

### 2.3. Enemies

Enemies are classified into three categories, each with different behaviors:
- **Light**: Low health, fast movement, slow firing.
- **Medium**: Multiple shots, normal movement, medium health.
- **Advanced**: Fast firing, high health, slow movement.

### 2.4. Bosses

The game currently includes one boss for the first level:
- **Marcus**: A boss armed with a Pacifier pistol, attacking with waves of shots and heat-seeking missiles.

### 2.5. Progression

- The game features **automatic horizontal scrolling**, with several checkpoints that allow the player to improve their character's abilities. 
- **Level 1: Depths of Zaun** – A run-down, poor environment where the player fights Pacifiers to progress.

### 2.6. Power-ups

- **Red Buff**: Increases the player's attack speed.
- **Blue Buff**: Increases the player's movement speed.

### 2.7. Cheat / Debug Menu

- A debug menu can be accessed via the **Konami Code**, allowing the player to become invincible to test game mechanics without dying.

## 3. Planned Features (Not Implemented)

- **Level 2: Piltover Bridge** – A planned level with a different theme, representing the bridge leading to Piltover. This level has not been developed yet.
- **Ambessa (Boss of Level 2)** – The boss for this level was planned with unique mechanics, including dash and multiple attacks.
- **Additional Playable Characters** – Vi and Jinx have planned sprites and abilities, but only the sprites have been created without full implementation.

## 4. Tools and Technologies Used

- **Game Engine**: SFML (Simple and Fast Multimedia Library) was used for graphics, sound, and user input management.
- **Pixel Art**: Piskel was used for creating pixel art sprites and animations.
- **Music**: The music is inspired by the soundtrack of *Arcane* to maintain immersion in the game's universe.

## 5. Inspirations

- **Star Wars Episode III: Revenge of the Sith** (DS): The perspective of the scenery and characters influenced the visual aspect of the game.
- **Ikaruga**: The strategic gameplay influence, where enemy movement and firing patterns are important.
- **Arcane** and **League of Legends**: The main inspiration for the game, particularly for the characters and the universe.

## 6. Controls

- **Movement**: Z Q S D
- **Shoot**: Left click
- **Ability 1**: A (the boomerang returns to the character)
- **Ability 2**: E 
- **Ability 3**: C (direction of the dash with the mouse)
- **Ultimate**: X

At the start, no abilities are unlocked. The player begins with one ability, and each 10 points unlocks a new ability. The ultimate ability is unlocked last.
To unlock an ability: `Ctrl` + `(ability key)`

- **Pause Menu**: Escape
- **Konami Code**: Up Up Down Down Left Right Left Right B A

## 7. Known Bugs

Due to time constraints, there are several known bugs:
- Restarting the game when the player dies causes the game to crash (it worked in previous commits).
- Possible crashes (no known cause).
- Issues with the ultimate ability, which is not always unlockable or usable.
