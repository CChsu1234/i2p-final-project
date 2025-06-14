# Team 04: Cube Sniper
## Abstract

Cube Sniper is a 3D shooting game inspired by Aim Lab, developed in C++ with custom 3D-to-2D projection using MVP matrices (referencing OpenGL) and the Eigen library.

The game features a login / signup system where passwords are hashed before being stored in user.txt for security.

Entering the game, you will see sign up / login scene. The password will be hashed before saved to user.txt, so the game developer cannot know the players' password directly.

There are two game modes:

1. Sixty Second Rush: Timed Mode. Train your shooting speed and accuracy.
2. Survive the Cube Assault: Survival Mode. Shoot the cube before it hits your face.

Game results are saved to scoreboard.txt. Players can view a line graph of their last 10 scores and the top scores of others.


## Game Features Comprehensively
Easy: Local Account System, Game Scene Design, 
Hard: 3D Engine, Online Double Players
### 3D Engine


### Start Scene
![image](https://hackmd.io/_uploads/H1mo0TKQxg.png)
The game will start and Start Scene. 

You can go to "play", "settings", "scoreboard" from this scene.
However, you haven't login yet, so if you press play or setting, it will jump to login scene. 

The background is decorated with multiple colorful rotating cubes. You can change your camera direction by moving your mouse. You can refer to CubeBackground class.

### Login Scene

![image](https://hackmd.io/_uploads/Hy8lx0Fmgx.png)
If you haven’t signed up yet, click the Sign Up button at the top-right corner to switch to sign-up mode.

![image](https://hackmd.io/_uploads/ryARlCYQll.png)
The sign-up scene uses a custom TextEditor class. Enter your username (top field) and password (bottom field). You can toggle password visibility using the eye icon. 
Passwords are hashed before being saved to scoreboard.txt.

It will show relevant message on screen if user already exists.

If the username already exists, an on-screen message will appear. After successfully signing up, you’ll return to the login scene.

During login, if the username doesn’t exist or the password is incorrect, a relevant error message will be shown. Upon successful login, you’ll proceed to the Start Scene.

### Setting Scene

![image](https://hackmd.io/_uploads/H1KXCe5Xge.png)
Click the crosshair image to change your crosshair in games. The default crosshair is blue.

### Mode Select Scene
![image](https://hackmd.io/_uploads/H1qLV0FXeg.png)

If you press play button in start scene, you will be directed to Mode Select Scene. 

In this scene, you select the game mode and enter the game.

### GameScene Timed Mode: Sixty-Second Rush
<iframe width="560" height="315" src="https://www.youtube.com/embed/T_mE24iiS9A?si=4gWmDrp-mHpgt3E1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

In this timed mode, three target cubes spawn at the start. Players control the camera using the mouse and shoot by clicking. Destroyed targets respawn instantly. Each hit increases the score, while misses result in a penalty. The game lasts for 60 seconds and records both the player’s score and accuracy.

### GameScene Survival Mode: Survive Cube Assault
<iframe width="560" height="315" src="https://www.youtube.com/embed/dFGpZQs01rc?si=7GF9a-4u918LrCQH" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

In this survival mode, target cubes spawn at random locations and move toward the player. The player must eliminate them before they get too close; otherwise, they lose life. When the cube hits the player, there will be a red flash animation. The game ends when the player’s lives count reaches zero. As time progresses, the spawn rate and the speed of target cubes increases, raising the difficulty level.


### ScoreBoard Scene

![image](https://hackmd.io/_uploads/Hy1Wan57ex.png)
![image](https://hackmd.io/_uploads/r1m-QJc7lg.png)

You can go to ScoreBoard Scene from the EndScene of two game mode. The left size lists the best score of other plays. The line graph showcasts at most your past 10 scores, depending on how many times you played.

### Online Double Players


## Individual Contribution 
113062302 許至曦: Online Double Players, 3D Engine 60%, ScoreBoard, Local Account System

113062321 高子鈞: 3D Engine 40%, Setting, Sixty-Second Rush, Survive Cube Assualt, UI beautify, background design.