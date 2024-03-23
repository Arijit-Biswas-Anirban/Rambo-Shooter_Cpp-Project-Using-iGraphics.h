/*
Game Project By: Arijit Biswas Anirban
Student ID: 220112
Pabna University of Science and Technology
*/

#include <iostream>
#include <string.h>
#include <cstdlib>
#include "iGraphics.h"

using namespace std;
#define SCREEN_WIDTH 1520
#define SCREEN_HEIGHT 792
#define IDLE_ANIMATION_SPEED 250 
#define LOADING_ANIMATION_SPEED 110
#define BACKGROUND_ANIMATION_SPEED 2
#define BULLET_SPEED 12
#define MAX_JUMP_HEIGHT 100	
#define MAX_BULLETS 5	
#define HEALTH_BAR_WIDTH 400
#define HEALTH_BAR_HEIGHT 50
#define BULLET_WIDTH 15
#define BULLET_HEIGHT 10
#define MAX_ZOMBIES 12
#define ZOMBIE_WIDTH 200
#define ZOMBIE_HEIGHT 300
#define ZOMBIE_RUNNING_ANIMATION_SPEED 3
#define ZOMBIE_ATTACK_ANIMATION_SPEED 5  
#define BULLET_DAMAGE 1

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Variables Here:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// Variables to track whether the game has started and Starting game theme image
bool loadingStarted = true;		
int load_flag = 0;				
bool gameStarted = false;		
int gameThemeImage;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Loading <-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
int load_images[12];
int currentLoadImage = 0;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Background <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// Background image position
double background_x = 0;
// Background ground position
double background_ground_x = 0;

int background1, background2, background3, background4, background5;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> MENU <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

bool inMenu = false;
bool inAbout = false;
bool inScore = false;
bool inHowtoplay = false;

int menuImage;
int aboutImage;
int scoreImage;
int howToPlayImage;
enum MenuButton{ PLAY, SCORE, CONTROLS, ABOUT };
MenuButton selectedButton = PLAY;

bool play_is_true = false;
bool about_is_true = false;
bool score_is_true = false;
bool how_to_play_is_true = false;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Player <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// Player position
int player_x = 150, player_y = 110;

// Arrays to store player right images
int player_right_idle_images[4]; 
int player_right_running_images[8]; 
int player_right_jump_images[6]; 
int player_right_downfall_images[6]; 

// Arrays to store player left images
int player_left_idle_images[4]; 
int player_left_running_images[8]; 
int player_left_jump_images[6]; 
int player_left_downfall_images[6]; 

// Player Health
int currentHealthImage = 10;
int playerHealth = 100; // Initial health
int player_health_images[11]; 

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Player State <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// Variables to check player er state
enum PlayerState { IDLE, RUNNING_LEFT, RUNNING_RIGHT, JUMPING, DOWNFALL };
PlayerState playerState = IDLE;	// bortoman state of player
int currentPlayerImage = 0;

// Variable to track the player's view (right or left) and state (running, idle, or jumping)
bool isRightView = true; 
bool isRunning = false;  
bool isJumping = false; 
int jumpHeight = 0;    

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Bullet <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// Image IDs for the bullet images
int bullet_right_image, bullet_left_image;

// Bullet structure 
struct Bullet
{
	int x, y;
	bool isRight;
	bool isActive;
};

Bullet bullets[MAX_BULLETS];	// Number of bullets

bool bulletSoundPlaying = false;
bool isSoundPlaying = false;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Zombie <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// Constants
int currentZombie = 0;
const int ZOMBIE_SPEED = 50;
const int ZOMBIE_ATTACK_DAMAGE = 2;
const int MAX_PLAYER_HEALTH = 100;
const int MAX_ZOMBIE_HEALTH = 3;


struct Zombie {
	float x, y;            // Zombie position
	int health;
	int currentZombieImages;
	int currentZombieRunningImage;
	int currentZombieAttackImage;
	int currentZombieRunningImageCounter;
	int currentZombieAttackImageCounter;
	bool isActive;         
	bool isDie;
	bool isRunning;        
	bool isAttacking;      
};

// Maximum number of zombies
Zombie zombies[MAX_ZOMBIES];

// Load zombie images
int zombie_running_images[10]; 
int zombie_attack_images[10]; 

// Function to check songhorso between player and bullet
bool IsCollisionPlayer(int x1, int width1, int x2) {
	if ((x1 + width1 - 100 >= x2) && (x2 + ZOMBIE_WIDTH - 100 > x1))
		return true;
	else
		return false;
}

bool IsCollisionBullet(bool isRight, int bulletX, int bulletWidth, int zombieX, int zombieWidth) {
	if (isRight) {
		// Check bullet right dik e collision korse ki na
		return (bulletX + bulletWidth - 75 >= zombieX && bulletX <= zombieX + zombieWidth);
	}
	else {
		//Check bullet left dik e collision korse ki na
		return (bulletX <= zombieX + zombieWidth && bulletX + bulletWidth >= zombieX);
	}
}

float playerScore = 0;
float currentScore = 0;
float maxScore = 0;

bool gameOver = false;
int scoreImages[5];


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Load images <-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//Function to load loading images
void LoadLoadingImages()
{
	load_images[0] = iLoadImage("Resources\\Loading\\loading_01.png");
	load_images[1] = iLoadImage("Resources\\Loading\\loading_02.png");
	load_images[2] = iLoadImage("Resources\\Loading\\loading_03.png");
	load_images[3] = iLoadImage("Resources\\Loading\\loading_04.png");
	load_images[4] = iLoadImage("Resources\\Loading\\loading_05.png");
	load_images[5] = iLoadImage("Resources\\Loading\\loading_06.png");
	load_images[6] = iLoadImage("Resources\\Loading\\loading_07.png");
	load_images[7] = iLoadImage("Resources\\Loading\\loading_08.png");
	load_images[8] = iLoadImage("Resources\\Loading\\loading_08.png");
	load_images[9] = iLoadImage("Resources\\Loading\\loading_10.png");
	load_images[10] = iLoadImage("Resources\\Loading\\loading_11.png");
	load_images[11] = iLoadImage("Resources\\Loading\\loading_12.png");
}

//Function to load menu images
void LoadMenuImages()
{
	menuImage = iLoadImage("Resources\\Menu\\menu.png");
	aboutImage = iLoadImage("Resources\\Menu\\About\\about.png");
	scoreImage = iLoadImage("Resources\\Score\\score_main.png");
	howToPlayImage = iLoadImage("Resources\\Menu\\how_to_play.png");
}

// Function to load background images
void LoadBackgroundImages()
{
	background1 = iLoadImage("Resources\\Background\\bg_01.png");
	background2 = iLoadImage("Resources\\Background\\bg_02.png");
	background3 = iLoadImage("Resources\\Background\\bg_03.png");
	background4 = iLoadImage("Resources\\Background\\bg_04.png");
	background5 = iLoadImage("Resources\\Background\\bg_05.png");
}

// Function to load player images
void LoadPlayerImages()
{
	// Front or Right view of player
	// Idle images
	player_right_idle_images[0] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_01.png");
	player_right_idle_images[1] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_02.png");
	player_right_idle_images[2] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_03.png");
	player_right_idle_images[3] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_04.png");

	// Running images
	player_right_running_images[0] = iLoadImage("Resources\\Player\\playerRun\\pl_run_01.png");
	player_right_running_images[1] = iLoadImage("Resources\\Player\\playerRun\\pl_run_02.png");
	player_right_running_images[2] = iLoadImage("Resources\\Player\\playerRun\\pl_run_03.png");
	player_right_running_images[3] = iLoadImage("Resources\\Player\\playerRun\\pl_run_04.png");
	player_right_running_images[4] = iLoadImage("Resources\\Player\\playerRun\\pl_run_05.png");
	player_right_running_images[5] = iLoadImage("Resources\\Player\\playerRun\\pl_run_06.png");
	player_right_running_images[6] = iLoadImage("Resources\\Player\\playerRun\\pl_run_07.png");
	player_right_running_images[7] = iLoadImage("Resources\\Player\\playerRun\\pl_run_08.png");

	// Jump images
	player_right_jump_images[0] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_01.png");
	player_right_jump_images[1] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_02.png");
	player_right_jump_images[2] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_03.png");
	player_right_jump_images[3] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_04.png");
	player_right_jump_images[4] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_05.png");
	player_right_jump_images[5] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_06.png");
	player_right_downfall_images[0] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_07.png");
	player_right_downfall_images[1] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_08.png");
	player_right_downfall_images[2] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_09.png");
	player_right_downfall_images[3] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_10.png");
	player_right_downfall_images[4] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_11.png");
	player_right_downfall_images[5] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_12.png");

	// Back or Left view of player
	// Idle images
	player_left_idle_images[0] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_back_01.png");
	player_left_idle_images[1] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_back_02.png");
	player_left_idle_images[2] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_back_03.png");
	player_left_idle_images[3] = iLoadImage("Resources\\Player\\playerIdle\\pl_idle_back_04.png");

	// Running images
	player_left_running_images[0] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_01.png");
	player_left_running_images[1] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_02.png");
	player_left_running_images[2] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_03.png");
	player_left_running_images[3] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_04.png");
	player_left_running_images[4] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_05.png");
	player_left_running_images[5] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_06.png");
	player_left_running_images[6] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_07.png");
	player_left_running_images[7] = iLoadImage("Resources\\Player\\playerRun\\pl_run_back_08.png");

	// Jump images
	player_left_jump_images[0] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_01.png");
	player_left_jump_images[1] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_02.png");
	player_left_jump_images[2] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_03.png");
	player_left_jump_images[3] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_04.png");
	player_left_jump_images[4] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_05.png");
	player_left_jump_images[5] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_06.png");
	player_left_downfall_images[0] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_07.png");
	player_left_downfall_images[1] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_08.png");
	player_left_downfall_images[2] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_09.png");
	player_left_downfall_images[3] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_10.png");
	player_left_downfall_images[4] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_11.png");
	player_left_downfall_images[5] = iLoadImage("Resources\\Player\\playerJump\\pl_jump_back_12.png");
}

//Function to load bullet images
void LoadBulletImages()
{
	bullet_right_image = iLoadImage("Resources\\Firing\\Bullet.png");
	bullet_left_image = iLoadImage("Resources\\Firing\\Bullet_back.png");
}

//Function to load player health images
void LoadHealthImages()
{
	player_health_images[0] = iLoadImage("Resources\\PlayerHealth\\health_bar000.png");
	player_health_images[1] = iLoadImage("Resources\\PlayerHealth\\health_bar001.png");
	player_health_images[2] = iLoadImage("Resources\\PlayerHealth\\health_bar002.png");
	player_health_images[3] = iLoadImage("Resources\\PlayerHealth\\health_bar003.png");
	player_health_images[4] = iLoadImage("Resources\\PlayerHealth\\health_bar004.png");
	player_health_images[5] = iLoadImage("Resources\\PlayerHealth\\health_bar005.png");
	player_health_images[6] = iLoadImage("Resources\\PlayerHealth\\health_bar006.png");
	player_health_images[7] = iLoadImage("Resources\\PlayerHealth\\health_bar007.png");
	player_health_images[8] = iLoadImage("Resources\\PlayerHealth\\health_bar008.png");
	player_health_images[9] = iLoadImage("Resources\\PlayerHealth\\health_bar009.png");
	player_health_images[10] = iLoadImage("Resources\\PlayerHealth\\health_bar010.png");
}

void LoadZombieImages() {
	// Load zombie running images
	zombie_running_images[0] = iLoadImage("Resources\\Zombie1\\Running\\Run_000.png");
	zombie_running_images[1] = iLoadImage("Resources\\Zombie1\\Running\\Run_001.png");
	zombie_running_images[2] = iLoadImage("Resources\\Zombie1\\Running\\Run_002.png");
	zombie_running_images[3] = iLoadImage("Resources\\Zombie1\\Running\\Run_003.png");
	zombie_running_images[4] = iLoadImage("Resources\\Zombie1\\Running\\Run_004.png");
	zombie_running_images[5] = iLoadImage("Resources\\Zombie1\\Running\\Run_005.png");
	zombie_running_images[6] = iLoadImage("Resources\\Zombie1\\Running\\Run_006.png");
	zombie_running_images[7] = iLoadImage("Resources\\Zombie1\\Running\\Run_007.png");
	zombie_running_images[8] = iLoadImage("Resources\\Zombie1\\Running\\Run_008.png");
	zombie_running_images[9] = iLoadImage("Resources\\Zombie1\\Running\\Run_009.png");

	// Load zombie attack images
	zombie_attack_images[0] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_000.png");
	zombie_attack_images[1] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_001.png");
	zombie_attack_images[2] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_002.png");
	zombie_attack_images[3] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_003.png");
	zombie_attack_images[4] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_004.png");
	zombie_attack_images[5] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_005.png");
	zombie_attack_images[6] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_006.png");
	zombie_attack_images[7] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_007.png");
	zombie_attack_images[8] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_008.png");
	zombie_attack_images[9] = iLoadImage("Resources\\Zombie1\\Attacking\\Attack_009.png");
}

void LoadScoreImages()
{
	scoreImages[0] = iLoadImage("Resources\\Score\\score.png");
	scoreImages[1] = iLoadImage("Resources\\Score\\score_0.png");
	scoreImages[2] = iLoadImage("Resources\\Score\\score_1.png");
	scoreImages[3] = iLoadImage("Resources\\Score\\score_2.png");
	scoreImages[4] = iLoadImage("Resources\\Score\\score_3.png");
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Show Images <-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void DisplayLoadingImages()
{
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, load_images[currentLoadImage]);
}

void DisplayGameTheme()
{
	int gameThemeImage = iLoadImage("Resources\\Theme\\theme_01.png");
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameThemeImage);
}

void DisplayMenuImage()
{
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuImage);
}

void DisplayScoreImage()
{
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, scoreImage);
	if (score_is_true)
	{
		char currentScoreText[50];
		sprintf_s(currentScoreText, " %.0f", currentScore);
		iText(770, 163, currentScoreText, GLUT_BITMAP_TIMES_ROMAN_24);

		maxScore = max(maxScore, currentScore);
		char maxScoreText[50];
		sprintf_s(maxScoreText, " %.0f", maxScore);
		iText(770, 236, maxScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void DisplayAboutImage()
{
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, aboutImage);
}

void DisplayHowToPlayImage(){
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, howToPlayImage);
}

void display_background()
{
	// Calculate the position of the second set of background images
	double background2_x = background_x + 4 * SCREEN_WIDTH;  // for background image

	// Display the first set of background images
	iShowImage(background_x, 80, SCREEN_WIDTH, 712, background1);
	iShowImage(background_x + SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background2);
	iShowImage(background_x + 2 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background3);
	iShowImage(background_x + 3 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background4);
	iShowImage(background_x + 4 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background5);


	iShowImage(background2_x, 80, SCREEN_WIDTH, 712, background1);
	iShowImage(background2_x + SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background2);
	iShowImage(background2_x + 2 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background3);
	iShowImage(background2_x + 3 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background4);
	iShowImage(background2_x + 4 * SCREEN_WIDTH, 80, SCREEN_WIDTH, 712, background5);

}

// Function to display the player's animation based on the state
void display_player()
{
	//Player right views
	if (isRightView)
	{
		// Display right running animation
		if (isRunning)
		{
			iShowImage(player_x, player_y, 150, 225, player_right_running_images[currentPlayerImage]);
		}
		// Display right jump animation
		else if (isJumping)
		{
			iShowImage(player_x, player_y, 150, 225, player_right_jump_images[currentPlayerImage]);
		}
		// Display right downfall animation
		else if (playerState == DOWNFALL)
		{
			iShowImage(player_x, player_y, 150, 225, player_right_downfall_images[currentPlayerImage]);
		}
		// Display right idle animation
		else
		{
			iShowImage(player_x, player_y, 150, 225, player_right_idle_images[currentPlayerImage]);
		}
	}

	//Player left views
	else
	{
		// Display left running animation
		if (isRunning)
		{
			iShowImage(player_x, player_y, 150, 225, player_left_running_images[currentPlayerImage]);
		}
		// Display left jump animation
		else if (isJumping)
		{
			iShowImage(player_x, player_y, 150, 225, player_left_jump_images[currentPlayerImage]);
		}
		// Display left downfall animation
		else if (playerState == DOWNFALL)
		{
			iShowImage(player_x, player_y, 150, 225, player_left_downfall_images[currentPlayerImage]);
		}
		// Display left idle animation
		else
		{
			iShowImage(player_x, player_y, 150, 225, player_left_idle_images[currentPlayerImage]);
		}
	}
}

// Function to display the bullets animation based on the state
void Display_bullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		// i'th bullet becomes active
		if (bullets[i].isActive)
		{
			// Move the bullet to the right
			if (bullets[i].isRight)
			{
				iShowImage(bullets[i].x, bullets[i].y, BULLET_WIDTH, BULLET_HEIGHT, bullet_right_image);
				bullets[i].x += BULLET_SPEED;
			}
			// Move the bullet to the left
			else
			{
				iShowImage(bullets[i].x, bullets[i].y, 15, 10, bullet_left_image);
				bullets[i].x -= BULLET_SPEED;
			}

			// Check if the bullet has gone off the screen
			if (bullets[i].x < 0 || bullets[i].x > SCREEN_WIDTH)
			{
				bullets[i].isActive = false; // Reset the i'th bullet when the bullet is out of bounds
			}
		}
	}
}

void Display_healthbar()
{
	iShowImage(40, 700, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, player_health_images[currentHealthImage]);

	// Check for collision with the player
	for (int i = 0; i < MAX_ZOMBIES; i++)
	{
		if (IsCollisionPlayer(player_x, 150, zombies[i].x) && (zombies[i].currentZombieAttackImage == 6) && zombies[i].isAttacking)
		{
			playerHealth -= ZOMBIE_ATTACK_DAMAGE;
			if (playerHealth % 10 == 0 && playerHealth != 100)
				currentHealthImage--;
			// Player hit by zombie, decrease score
			playerScore -= 10;
			currentScore = playerScore;
		}
		// Game over condition
		if (currentHealthImage <= 0)
		{
			gameOver = true;
			play_is_true = false;
		}

	}

}

void Display_score()
{
	if (gameOver)
	{
		if (playerScore < (MAX_ZOMBIES * 300) / 3.0)
		{
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, scoreImages[1] = iLoadImage("Resources\\Score\\score_0.png"));
			iSetColor(0, 0, 0);

			char scoreText[50];
			sprintf_s(scoreText, " %.0f", playerScore);
			iText(770, 163, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else if (playerScore >= ((MAX_ZOMBIES * 300) / 3.0) && playerScore < ((MAX_ZOMBIES * 300) / 1.5))
		{
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, scoreImages[1] = iLoadImage("Resources\\Score\\score_1.png"));
			iSetColor(0, 0, 0);

			char scoreText[50];
			sprintf_s(scoreText, " %.0f", playerScore);
			iText(770, 163, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else if (playerScore >= ((MAX_ZOMBIES * 300) / 1.5) && playerScore < ((MAX_ZOMBIES * 300) / 1.0))
		{
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, scoreImages[1] = iLoadImage("Resources\\Score\\score_2.png"));
			iSetColor(0, 0, 0);

			char scoreText[50];
			sprintf_s(scoreText, " %.0f", playerScore);
			iText(770, 163, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else if (playerScore >= ((MAX_ZOMBIES * 300) / 1.0) || playerScore == ((MAX_ZOMBIES * 300) / 1.0))
		{
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, scoreImages[1] = iLoadImage("Resources\\Score\\score_3.png"));
			iSetColor(0, 0, 0);

			char scoreText[50];
			sprintf_s(scoreText, " %.0f", playerScore);
			iText(770, 163, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> Player Animation <-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void UpdateLoadingAnimation()
{
	currentLoadImage++;
	load_flag;
	if (currentLoadImage == 12 && load_flag == 1)
	{
		loadingStarted = false;
		currentLoadImage = 0;
	}
	else if (currentLoadImage == 12 && load_flag == 0)
	{
		load_flag++;
		currentLoadImage = 0;
	}

}

void UpdatePlayerAnimation()
{
	// Increment the image index for the next frame
	currentPlayerImage++;

	// Reset jump state when the player reaches max jump height
	if (isJumping && jumpHeight >= MAX_JUMP_HEIGHT)
	{
		isJumping = false;
		jumpHeight = 0;		// Player return on ground
	}

	// Controll jumping and downfall animation
	if (playerState == JUMPING && currentPlayerImage == 6)
	{
		playerState = DOWNFALL;		// Players jump full, ekon nambe 
		currentPlayerImage = 0;
	}
	else if (playerState == DOWNFALL && currentPlayerImage == 6)
	{
		playerState = IDLE;			//  Players downfall animation successful
		currentPlayerImage = 0;
	}

	// Determine the number of frames based on player state
	int maxImages = 0;
	if (isRunning)
	{
		maxImages = 8;			
	}
	else if (playerState == JUMPING || playerState == DOWNFALL)
	{
		maxImages = 6;				
	}
	else
	{
		maxImages = 4;				
	}

	if (currentPlayerImage >= maxImages)
	{
		currentPlayerImage = 0;		// Reset image index
	}
}

void handleMenuButtonClick() {

	switch (selectedButton) {
	case PLAY:
		inMenu = false;
		play_is_true = true;
		break;
	case SCORE: 
		inMenu = false;
		inScore = true;
		score_is_true = true;
		break;
	case CONTROLS:
		inMenu = false;
		inHowtoplay = true;
		how_to_play_is_true = true;
		break;
	case ABOUT:
		inMenu = false;
		inAbout = true;
		about_is_true = true;
		break;
	}
}


// Function to update zombie positions and states 
void UpdateZombies() {
	if (play_is_true){
		for (int i = 0; i < MAX_ZOMBIES; i++) {
			if (zombies[i].isActive && !zombies[i].isDie && zombies[i].isRunning) {
				if (zombies[i].x < 0) {
					zombies[i].isDie = true;
					zombies[i].isActive = false;
					currentZombie++;
				}

				zombies[i].x -= ZOMBIE_SPEED;
				// Check if the zombie's health is zero or below
				if (zombies[i].health <= 0) {
					zombies[i].isDie = true;
					zombies[i].isActive = false;
					// Zombie killed, score barbe
					playerScore += 300;
					currentScore = playerScore;
					currentZombie++;
				}

				if (currentZombie == MAX_ZOMBIES)
				{
					gameOver = true;
					play_is_true = false;
					Display_score();
				}

				// Check for collision with bullets
				for (int j = 0; j < MAX_BULLETS; j++) {
					if (bullets[j].isActive && IsCollisionBullet(bullets[j].isRight, bullets[j].x, BULLET_WIDTH, zombies[i].x, ZOMBIE_WIDTH)) {
						zombies[i].health -= BULLET_DAMAGE;  
						bullets[j].isActive = false;  // hit bullet deactivate
					}
				}

				// Slow down the running animation
				zombies[i].currentZombieRunningImageCounter++;
				if (zombies[i].currentZombieRunningImageCounter >= ZOMBIE_RUNNING_ANIMATION_SPEED) {
					zombies[i].currentZombieRunningImage++;
					if (zombies[i].currentZombieRunningImage >= 9) {
						zombies[i].currentZombieRunningImage = 0;
					}
					zombies[i].currentZombieRunningImageCounter = 0;  
				}

				// Slow down the attacking animation
				zombies[i].currentZombieAttackImageCounter++;
				if (zombies[i].currentZombieAttackImageCounter >= ZOMBIE_ATTACK_ANIMATION_SPEED) {
					zombies[i].currentZombieAttackImage++;
					if (zombies[i].currentZombieAttackImage >= 9) {
						zombies[i].currentZombieAttackImage = 0;
					}
					zombies[i].currentZombieAttackImageCounter = 0;  
				}
			}
		}
	}
}


void DisplayZombies() {
	for (int i = 0; i < MAX_ZOMBIES; i++) {
		if (zombies[i].isActive) {
			zombies[i].currentZombieRunningImage++;
			zombies[i].currentZombieAttackImage++;

			if (IsCollisionPlayer(player_x, 150, zombies[i].x)) {
				zombies[i].isRunning = false;
				zombies[i].isAttacking = true;
			}
			if (!IsCollisionPlayer(player_x, 150, zombies[i].x))
			{
				zombies[i].isRunning = true;
				zombies[i].isAttacking = false;
			}
			if (zombies[i].isActive && zombies[i].isAttacking) {
				iShowImage(zombies[i].x, zombies[i].y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_attack_images[zombies[i].currentZombieAttackImage]);
			}
			else if (zombies[i].isActive && zombies[i].isRunning) {
				iShowImage(zombies[i].x, zombies[i].y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_running_images[zombies[i].currentZombieRunningImage]);
			}

			if (zombies[i].currentZombieRunningImage >= 9) {
				zombies[i].currentZombieRunningImage = 0;
			}
			if (zombies[i].currentZombieAttackImage >= 9) {
				zombies[i].currentZombieAttackImage = 0;
			}
		}
	}
}

// Function to control music play
void controlSound() {
	if (!gameStarted){
		PlaySound("Resources\\Music\\game.wav", NULL, SND_LOOP | SND_ASYNC);
	}
}



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-> iDraw <-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();
	//If the game hasn't started, display loading images
	if (loadingStarted)
	{
		DisplayLoadingImages();
	}
	else	
	{
		//Display the theme image
		if (!gameStarted)
		{
			DisplayGameTheme();
		}
		// game start hoise enter chepe
		else
		{
			if (inMenu)
			{
				DisplayMenuImage();
			}
			else if (play_is_true)
			{
				if (jumpHeight > 0)
				{
					jumpHeight -= 2;
				}
				// update jump height
				if (isJumping)
				{
					// Player is on right view
					if (isRightView)
					{
						player_x += 5;
					}
					// Player is on left view
					else
					{
						player_x -= 5;
					}

					// Player reached max height
					if (jumpHeight >= MAX_JUMP_HEIGHT)
					{
						isJumping = false;
						playerState = DOWNFALL;
					}
					// Player hasn't reached max height
					else
					{
						player_y += 5;
						jumpHeight += 5;
					}
				}
				else if (playerState == DOWNFALL)
				{
					// Player is on right view
					if (isRightView)
					{
						player_x += 5;
					}
					// Player is on left view
					else
					{
						player_x -= 5;
					}

					player_y -= 5;	// player height kombe

					// Player can not go under the background ground image
					if (player_y <= 110)
					{
						player_y = 110;
						playerState = IDLE;
					}
				}
				// During Jumping player becomes idle by pressing any key
				else
				{
					if (player_y > 110)
					{
						player_y -= 5;
					}
					else
					{
						player_y = 110;
					}
				}

				// update player position if touch the screen
				if (player_x < 0)
				{
					player_x = 0;
				}
				if (player_x >= SCREEN_WIDTH - 150)
				{
					player_x = SCREEN_WIDTH - 150;
				}

				// Background moving animation
				if (isRightView)
				{
					background_x -= BACKGROUND_ANIMATION_SPEED;
					background_ground_x -= BACKGROUND_ANIMATION_SPEED;
				}
				else
				{
					background_x += BACKGROUND_ANIMATION_SPEED;
					background_ground_x += BACKGROUND_ANIMATION_SPEED;
				}
				
				// If the first set of background images goes off the screen, reset its position to the right
				if (isRightView)
				{
					if (background_x < 4 * -SCREEN_WIDTH)
					{
						background_x = 0;
					}
				}
				else
				{
					if (background_x >= 0)
					{
						background_x = 4 * -SCREEN_WIDTH;
					}
				}
				// Function to Display Images
				display_background();
				display_player();
				Display_bullets();
				// Update and display zombies
				DisplayZombies();

				// Display player health bar
				Display_healthbar();
				// Display the player's score at the top middle of the screen
				iShowImage(SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT - 50, 150, 50, scoreImages[0]);
				iSetColor(255, 255, 100);

				char scoreText[50];
				sprintf_s(scoreText, " %.0f", playerScore);
				iText(SCREEN_WIDTH / 2 + 25, SCREEN_HEIGHT - 33, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else if (about_is_true){
				DisplayAboutImage();
			}
			else if (score_is_true){
				DisplayScoreImage();
			}
			else if (how_to_play_is_true){
				DisplayHowToPlayImage();
			}
			else if (gameOver){
				Display_score();
			}
		}
	}
}

/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (inMenu) {
			
			if (mx >= 865 && mx <= 1130 && my >= 317 && my <= 367) {
				selectedButton = PLAY;
				handleMenuButtonClick();
			}
			
			else if (mx >= 865 && mx <= 1130 && my >= 249 && my <= 299) {
				selectedButton = SCORE;
				handleMenuButtonClick();
			}
			
			else if (mx >= 865 && mx <= 1130 && my >= 181 && my <= 231) {
				selectedButton = CONTROLS;
				handleMenuButtonClick();
			}
			
			else if (mx >= 865 && mx <= 1130 && my >= 113 && my <= 163) {
				selectedButton = ABOUT;
				handleMenuButtonClick();
			}
		}
		else if (inAbout) {
			if (mx >= 627 && mx <= 892 && my >= 36 && my <= 86) {
				inAbout = false;
				about_is_true = false;
				inMenu = true;
			}
		}
		else if (inScore) {
			if (mx >= 640 && mx <= 725 && my >= 48 && my <= 129){
				inScore = false;
				score_is_true = false;
				inMenu = true;
				playerHealth = 100;
				currentHealthImage = 10;
				playerScore = 0;
				currentZombie = 0;
				for (int i = 0, j = 1; i < MAX_ZOMBIES; i++, j += 2) {
					zombies[i].isActive = true;
					zombies[i].isDie = false;
					zombies[i].health = MAX_ZOMBIE_HEALTH;
					zombies[i].currentZombieRunningImage = 0;
					zombies[i].currentZombieAttackImage = 0;
					zombies[i].currentZombieImages = 0;
					zombies[i].isRunning = true;  // zombies initially running
					zombies[i].isAttacking = false;
					zombies[i].x = SCREEN_WIDTH + (j * 250);  // Adjust initial x position of zombie
					zombies[i].y = 110;
					zombies[i].currentZombieRunningImageCounter = -5;
					zombies[i].currentZombieAttackImageCounter = -5;
				}
			}
			if (mx >= 793 && mx <= 878 && my >= 48 && my <= 129){
				inScore = false;
				score_is_true = false;
				play_is_true = true;
				playerHealth = 100;
				currentHealthImage = 10;
				playerScore = 0;
				currentZombie = 0;
				for (int i = 0, j = 1; i < MAX_ZOMBIES; i++, j += 2) {
					zombies[i].isActive = true;
					zombies[i].isDie = false;
					zombies[i].health = MAX_ZOMBIE_HEALTH;
					zombies[i].currentZombieRunningImage = 0;
					zombies[i].currentZombieAttackImage = 0;
					zombies[i].currentZombieImages = 0;
					zombies[i].isRunning = true;  // zombies initially running
					zombies[i].isAttacking = false;
					zombies[i].x = SCREEN_WIDTH + (j * 250);  // Adjust initial x position of zombie
					zombies[i].y = 110;
					zombies[i].currentZombieRunningImageCounter = -5;
					zombies[i].currentZombieAttackImageCounter = -5;
				}
			}

		}
		else if (inHowtoplay){
			if (mx >= 627 && mx <= 892 && my >= 36 && my <= 86) {
				inHowtoplay = false;
				how_to_play_is_true = false;
				inMenu = true;
			}
		}
		else if (gameOver){
			if (mx >= 640 && mx <= 725 && my >= 48 && my <= 129){
				gameOver = false;
				inMenu = true;
				playerHealth = 100;
				currentHealthImage = 10;
				playerScore = 0;
				currentZombie = 0;
				for (int i = 0, j = 1; i < MAX_ZOMBIES; i++, j += 2) {
					zombies[i].isActive = true;
					zombies[i].isDie = false;
					zombies[i].health = MAX_ZOMBIE_HEALTH;
					zombies[i].currentZombieRunningImage = 0;
					zombies[i].currentZombieAttackImage = 0;
					zombies[i].currentZombieImages = 0;
					zombies[i].isRunning = true;  // zombies initially running
					zombies[i].isAttacking = false;
					zombies[i].x = SCREEN_WIDTH + (j * 250);  // Adjust initial x position of zombie
					zombies[i].y = 110;
					zombies[i].currentZombieRunningImageCounter = -5;
					zombies[i].currentZombieAttackImageCounter = -5;
				}
			}
			if (mx >= 793 && mx <= 878 && my >= 48 && my <= 129){
				gameOver = false;
				play_is_true = true;
				playerHealth = 100;
				currentHealthImage = 10;
				playerScore = 0;
				currentZombie = 0;
				for (int i = 0, j = 1; i < MAX_ZOMBIES; i++, j += 2) {
					zombies[i].isActive = true;
					zombies[i].isDie = false;
					zombies[i].health = MAX_ZOMBIE_HEALTH;
					zombies[i].currentZombieRunningImage = 0;
					zombies[i].currentZombieAttackImage = 0;
					zombies[i].currentZombieImages = 0;
					zombies[i].isRunning = true;  // zombies initially running
					zombies[i].isAttacking = false;
					zombies[i].x = SCREEN_WIDTH + (j * 250);  // Adjust initial x position of zombie
					zombies[i].y = 110;
					zombies[i].currentZombieRunningImageCounter = -5;
					zombies[i].currentZombieAttackImageCounter = -5;
				}
			}
		}
	}
}


/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	// Starting the game by pressing Enter button
	if (key == 13) 
	{
		gameStarted = true;
		inMenu = true;
	}

	// Controlling Running state
	if (key == 'r' || key == 'R')
	{
		isRunning = true;
		isJumping = false; // Stop jumping when running
		playerState = RUNNING_RIGHT;
	}

	// Controlling Jumping state
	else if (key == ' ' || key == 'j' || key == 'J')
	{
		if (!isJumping && player_y == 110)
		{
			isJumping = true;
			jumpHeight = 0;
			playerState = JUMPING;
		}
	}

	// Controlling Firing state
	else if (key == 'f' || key == 'F')
	{
		// Fire only when player is on running state
		if (isRunning)
		{
			// Find an inactive bullet to fire
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (!bullets[i].isActive)
				{
					bullets[i].isActive = true;
					bullets[i].isRight = isRightView;
					// Right view
					if (bullets[i].isRight)
					{
						bullets[i].x = player_x + 120;	
					}
					// Left view
					else
					{
						bullets[i].x = player_x + 10;	
					}
					bullets[i].y = player_y + 90;		
					bulletSoundPlaying = true;
					break; // Stop after firing one bullet
				}
			}
		}
	}
	else
	{
		isRunning = false;
		playerState = IDLE;
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:

		// Player Right view states (Running, Jumping, Idle)
		isRightView = true;
		if (isRunning)
		{
			playerState = RUNNING_RIGHT;
			player_x += 15;
		}
		else if (isJumping)
		{
			playerState = JUMPING;
		}
		else
		{
			playerState = IDLE;
		}
		break;

	case GLUT_KEY_LEFT:

		// Player Left view states (Running, Jumping, Idle)
		isRightView = false;
		if (isRunning)
		{
			playerState = RUNNING_LEFT;
			player_x -= 15;
		}
		else if (isJumping)
		{
			playerState = JUMPING;
		}
		else
		{
			playerState = IDLE;
		}
		break;

	case GLUT_KEY_DOWN:

		// Reset Player state
		playerState = IDLE;
		isRunning = false;
		isJumping = false;
		break;

	default:
		playerState = IDLE;
		isRunning = false;
		isJumping = false;
		break;
	}
}

int main()
{
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Rambo-Shooter");

	// Initially, no bullets are active. Bullets will be activate by pressing 'f' or 'F'
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].isActive = false;
	}
	// Call the function to load player images, background images and bullet images
	LoadPlayerImages();
	LoadBulletImages();
	LoadBackgroundImages();
	LoadLoadingImages();
	LoadMenuImages();
	LoadHealthImages();
	LoadZombieImages();
	LoadScoreImages();
	for (int i = 0, j = 1; i < MAX_ZOMBIES; i++, j += 2) {
		zombies[i].isActive = true;
		zombies[i].isDie = false;
		zombies[i].health = MAX_ZOMBIE_HEALTH;
		zombies[i].currentZombieRunningImage = 0;
		zombies[i].currentZombieAttackImage = 0;
		zombies[i].currentZombieImages = 0;
		zombies[i].isRunning = true;  // zombies initially running
		zombies[i].isAttacking = false;
		zombies[i].x = SCREEN_WIDTH + (j * 250);  // Adjust initial x position of zombie
		zombies[i].y = 110;
		zombies[i].currentZombieRunningImageCounter = -5;
		zombies[i].currentZombieAttackImageCounter = -5;
	}

	iSetTimer(IDLE_ANIMATION_SPEED, UpdatePlayerAnimation);
	iSetTimer(LOADING_ANIMATION_SPEED, UpdateLoadingAnimation);
	iSetTimer(180, UpdateZombies);
	iSetTimer(65, controlSound);
	iStart();
	return 0;
}
