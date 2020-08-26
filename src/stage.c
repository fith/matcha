#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);
static void doEnemies(void);
static void doFighters(void);
static void clipPlayer(void);
static void resetStage(void);
static void fireEnemyBullet(Entity *e);
static int bulletHitFighter(Entity *b);
static void doBackground(void);
static void doStarfield(void);
static void doExplosions(void);
static void doDebris(void);
static void initStarfield(void);
static void drawBackground(void);
static void drawStarfield(void);
static void drawDebris(void);
static void drawExplosions(void);
static void drawHud(void);

static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *playerTexture;
static SDL_Texture *enemyBulletTexture;
static SDL_Texture *background;
static SDL_Texture *explosionTexture;
static int enemySpawnTimer;
static int stageResetTimer;
static Star stars[MAX_STARS];
static int backgroundX;
static int highscore;

void initStage(void)
{
  app.delegate.logic = logic;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;
  stage.explosionTail = &stage.explosionHead;
  stage.debrisTail = &stage.debrisHead;

  initPlayer();

  enemyBulletTexture = loadTexture("gfx/enemyBullet.png");
  bulletTexture = loadTexture("gfx/bullet.png");
  playerTexture = loadTexture("gfx/player.png");
  enemyTexture = loadTexture("gfx/enemy.png");
  explosionTexture = loadTexture("gfx/explosion.png");
  background = loadTexture("gfx/background.png");

  resetStage();
}

static void resetStage(void)
{
	Entity *e;
  Explosion *ex;
  Debris *d;
	
	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}
	
	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}

  while (stage.explosionHead.next)
  {
    ex = stage.explosionHead.next;
    stage.explosionHead.next = ex->next;
    free(ex);
  }

  while (stage.debrisHead.next)
  {
    d = stage.debrisHead.next;
    stage.debrisHead.next = d->next;
    free(d);
  }
	
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
  stage.explosionTail = &stage.explosionHead;
  stage.debrisTail = &stage.debrisHead;
  stage.score = 0;
	
	initPlayer();
  initStarfield();

  loadMusic("snd/music.wav");
	
	enemySpawnTimer = 0;
	
	stageResetTimer = FPS * 3;
}

static void initPlayer() 
{
  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->x = 100;
  player->y = 100;
  player->side = SIDE_PLAYER;
  player->health = 1;
  player->texture = playerTexture;
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void initStarfield(void)
{
  int i;

  for (i =0; i < MAX_STARS; i++)
  {
    stars[i].x = rand() % app.w;
    stars[i].y = rand() % app.h;
    stars[i].speed = 1 + rand() % 8;
  }
}

static void draw(void)
{
  drawBackground();

  drawStarfield();

  // printf("drawPlayer\n");
  drawPlayer();

  // printf("drawFighters\n");
  drawFighters();

  drawDebris();

  drawExplosions();

  // printf("drawBullets\n");
  drawBullets();

  drawHud();
}

static void logic(void)
{
  doBackground();

  doStarfield();

  // printf("doPlayer\n");
  doPlayer();

  // printf("doEnemies\n");
  doEnemies();

  // printf("doFighters\n");
  doFighters();

  // printf("doBullets\n");
  doBullets();
  
  doExplosions();

  doDebris();

  // printf("doSpawnEnemies\n");
  spawnEnemies();

  clipPlayer();

  // printf("Check for player daed.\n");
  if (player == NULL && --stageResetTimer <= 0)
  {
    // printf("Player dead and reset timed out.\n");
    resetStage();
  }
}

static void doBackground(void)
{
  if (--backgroundX < -app.w)
  {
    backgroundX = 0;
  }
}

static void doStarfield(void)
{
  int i;
  for(i = 0; i < MAX_STARS; i++)
  {
    stars[i].x -= stars[i].speed;

    if (stars[i].x < 0)
    {
      stars[i].x = app.w + stars[i].x;
    }
  }
}

static void doExplosions(void)
{
  Explosion *e, *prev;

  prev = &stage.explosionHead;

  for (e = stage.explosionHead.next; e != NULL; e = e->next)
  {
    e->x += e->dx;
    e->y += e->dy;

    if (--e->a <= 0)
    {
      if (e == stage.explosionTail)
      {
        stage.explosionTail = prev;
      }

      prev->next = e->next;
      free(e);
      e = prev;
    }

    prev = e;
  }
}

static void doDebris(void)
{
  Debris *d, *prev;

  prev = &stage.debrisHead;

  for (d = stage.debrisHead.next; d != NULL; d = d->next)
  {
    d->x += d->dx;
    d->y += d->dy;

    if (d->dx > 0) {
      d->dx -= 0.5;
    } else {
      d->dx = -PLAYER_SPEED;
    }

    if (d->dy > 0) {
      d->dy -= 0.1;
    } else if (d->dy < 0) {
      d->dy += 0.1;
    }

    if (--d->life <= 0)
    {
        if (d == stage.debrisTail)
        {
          stage.debrisTail = prev;
        }

        prev->next = d->next;
        free(d);
        d = prev;
    }

    prev = d;
  }
}

static void addExplosions(int x, int y, int num)
{
  Explosion *e;
  int i;

  for (i = 0; i < num; i++)
  {
    e = malloc(sizeof(Explosion));
    memset(e, 0, sizeof(Explosion));
    stage.explosionTail->next = e;
    stage.explosionTail = e;

    e->x = x + (rand() % 32) - (rand() % 32);
    e->y = y + (rand() %32) - (rand() % 32);
    e->dx = (rand() % 10) - (rand() % 10);
    e->dy = (rand() % 10) - (rand() % 10);

    e->dx /= 10;
    e->dy /= 10;

    switch (rand() % 4)
    {
      case 0:
        e->r = 255;
        break;
      case 1:
        e->r = 255;
        e->g = 128;
        break;
      case 2:
        e->r = 255;
        e->g = 255;
        break;
      default:
        e->r = 255;
        e->g = 255;
        e->b = 255;
        break;
    }
    e->a = rand() % FPS * 3;
  }
}

static void addDebris(Entity *e)
{
  Debris *d;
  int x, y, w, h;

  w = e->w / 2;
  h = e->h / 2;

  for (y = 0; y <= h; y += h)
  {
    for (x = 0; x <= w; x += w)
    {
      d = malloc(sizeof(Debris));
      memset(d, 0, sizeof(Debris));
      stage.debrisTail->next = d;
      stage.debrisTail = d;

      d->x = e->x + e->w / 2;
      d->y = e->y + e->h / 2;
      d->dy = (rand() % 5) - (rand() % 5);
      d->dx = (5 + (rand() % 12));
      d->life = FPS * 2;
      d->texture = e->texture;

      d->rect.x = x;
      d->rect.y = y;
      d->rect.w = w;
      d->rect.h = h;
    }
  }
}

static void fireBullet(void) 
{
  Entity *bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));
  stage.bulletTail->next = bullet;
  stage.bulletTail = bullet;

  bullet->x = player->x; 
  bullet->y = player->y;
  bullet->dx = PLAYER_BULLET_SPEED;
  bullet->health = 1;
  bullet->side = SIDE_PLAYER;
  bullet->texture = bulletTexture;
  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  bullet->y += (player->h / 2) - (bullet->h / 2);

  player->reload = 8;
}

static void doBullets(void)
{
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next)
  {
    b->x += b->dx;
    b->y += b->dy;

    if (bulletHitFighter(b) || 
        b->x < -b->w ||
        b->y < -b->h ||
        b->x > app.w ||
        b->y > app.h) 
    {
      if (b == stage.bulletTail)
      {
        stage.bulletTail = prev;
      }

      prev->next = b->next;
      free(b);
      b = prev;
    }

    prev = b;
  }
}

static int bulletHitFighter(Entity *b)
{
  Entity *e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next)
  {
    if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
    {
      b->health = 0;
      e->health = 0;

      addExplosions(e->x, e->y, 20);
      addDebris(e);

      if (e == player) {
        playSound(SND_PLAYER_DIE, CH_PLAYER);
      } else {
        playSound(SND_ENEMY_DIE, CH_ANY);
        stage.score++;
      }

      highscore = MAX(stage.score, highscore);

      return 1;
    }
  }
  return 0;
}

static void drawPlayer(void)
{
  if (player != NULL)
  {
    blit(player->texture, player->x, player->y);
  }
}

static void drawFighters(void) 
{
  Entity *e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next)
  {
    blit(e->texture, e->x, e->y);
  }
}

static void drawBullets(void)
{
  Entity *b;

  for (b = stage.bulletHead.next; b != NULL; b = b->next)
  {
    blit(b->texture, b->x, b->y);
  }
}

static void drawBackground(void)
{
  SDL_Rect dest;
  int x;

  for (x = backgroundX; x < app.w; x += app.w)
  {
    dest.x = x;
    dest.y = 0;
    dest.w = app.w;
    dest.h = app.h;

    SDL_RenderCopy(app.renderer, background, NULL, &dest);
  }
}

static void drawStarfield(void)
{
  int i, c;

  for(i = 0; i < MAX_STARS; i++)
  {
    c = 32 * stars[i].speed;

    SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

    SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
  }
}

static void drawDebris(void)
{
  Debris *d;

  for (d = stage.debrisHead.next; d != NULL; d = d->next)
  {
    blitRect(d->texture, &d->rect, d->x, d->y);
  }
}

static void drawExplosions(void)
{
  Explosion *e;

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

  for (e = stage.explosionHead.next; e != NULL; e = e->next) 
  {
    SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
    SDL_SetTextureAlphaMod(explosionTexture, e->a);

    blit(explosionTexture, e->x, e->y);
  }

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawHud(void)
{
  // drawText(10, 10, 255, 255, 255, "SCORE: %03d", stage.score);

  // if (stage.score > 0 && stage.score == highscore)
  // {
  //   drawText(520, 10, 0, 255, 0, "HIGH SCORE: %03d", highscore);
  // } 
  // else 
  // {
  //   drawText(520, 10, 255, 255, 255, "HIGH SCORE: %03d", highscore);
  // }
}

static void doPlayer(void)
{
  if (player != NULL) {
    player->dx = player->dy = 0;

    if (player->reload > 0) {
      player->reload--;
    }

    if(app.keyboard[SDL_SCANCODE_UP])
    {
      player->dy = -PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_DOWN])
    {
      player->dy = PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_LEFT])
    {
      player->dx = -PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_RIGHT])
    {
      player->dx = PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_SPACE] && player->reload == 0) 
    {
      fireBullet();
      playSound(SND_PLAYER_FIRE, CH_PLAYER);
    }

    player->x += player->dx;
    player->y += player->dy;
  }
}

static void doEnemies(void)
{
  Entity *e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next)
  {
    if (e != player && player != NULL && --e->reload <= 0 && e->x > player->x)
    {
      fireEnemyBullet(e);
      playSound(SND_ENEMY_FIRE, CH_ENEMY_FIRE);
    }
  }
}

static void doFighters(void) {
  Entity *e, *prev;

  prev = &stage.fighterHead;

  for (e = stage.fighterHead.next; e != NULL; e = e->next)
  {
    e->x += e->dx;
    e->y += e->dy;

    if (e != player && e->x < -e->w)
    {
      e->health = 0;
    }

    if (e->health == 0)
    {
      if (e == player) 
      {
        printf("Player died.\n");
        player = NULL;
      }

      if (e == stage.fighterTail) 
      {
        stage.fighterTail = prev;
      }

      prev->next = e->next;
      free(e);
      e = prev;
    }

    prev = e;
  }
}

static void fireEnemyBullet(Entity *e)
{
  Entity *bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));
  stage.bulletTail->next = bullet;
  stage.bulletTail = bullet;

  bullet->x = e->x;
  bullet->y = e->y;
  bullet->health = 1;
  bullet->texture = enemyBulletTexture;
  bullet->side = e->side;
  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  bullet->x += (e->w / 2) - (bullet->w / 2);
  bullet->y += (e->h / 2) - (bullet->h / 2);

  calcSlope(player->x + (player->w / 2), 
    player->y + (player->h / 2), 
    e->x, e->y, 
    &bullet->dx, &bullet->dy);

  bullet->dx *= ENEMY_BELLET_SPEED;
  bullet->dy *= ENEMY_BELLET_SPEED;

  bullet->side = SIDE_ENEMY;

  e->reload = (rand() % FPS * 2);
}

static void spawnEnemies(void) 
{
  Entity *enemy;

  if (--enemySpawnTimer <= 0)
  {
    enemy = malloc(sizeof(Entity));
    memset(enemy, 0, sizeof(Entity));
    stage.fighterTail->next = enemy;
    stage.fighterTail = enemy;

    enemy->texture = enemyTexture;
    SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
    enemy->x = app.w;
    enemy->y = rand() % (app.h - enemy->h);
    enemy->side = SIDE_ENEMY;
    enemy->health = 1;
    enemy->reload = FPS * (1 * (rand() % 3));

    enemy->dx = -(2 + (rand() % 4));
    
    enemySpawnTimer = 30 + (rand() % 60);
  }
}

static void clipPlayer(void)
{
  if (player != NULL)
  {
    if (player->x < 0)
    {
      player->x = 0;
    }

    if (player->y < 0)
    {
      player->y = 0;
    }

    if (player->x > app.w / 2)
    {
      player->x = app.w / 2;
    }

    if (player->y > app.h - player->h) 
    {
      player->y = app.h - player->h;
    }
  }
}