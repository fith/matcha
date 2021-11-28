#include "options.h"

static void logic(void);

static void draw(void);

static void deinitOptions(void);

static void createButton(char *str, int x, int y, void (*onClick)());

static UI *createUI(SDL_Texture *texNormal,
                    SDL_Texture *texHover,
                    SDL_Texture *texActive,
                    SDL_Color colNormal,
                    SDL_Color colHover,
                    SDL_Color colActive,
                    int x,
                    int y,
                    void(*onClick)(),
                    void(*onDrag)());

// Login
static void doButtons(void);

static void doUI(UI *ui);

// Draw
static void drawButtons(void);

static void drawUI(UI *ui);

// UI Events
static void clickBackButton(void);

static void toggleFullscreen(void);

static void toggleMusic(void);

static void toggleFilm(void);

// UI
static UI *backButton;
static UI *fullscreenToggle;
static UI *musicToggle;
static UI *filmToggle;
// UI Textures
static SDL_Texture *checked;
static SDL_Texture *unchecked;
static SDL_Texture *backTexture;

void initOptions(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.buttonsTail = &stage.buttonsHead;

    // UI - Textures
    checked = loadTexture("resources/gfx/checked.png");
    unchecked = loadTexture("resources/gfx/dot.png");
    backTexture = textTexture(FNT_BUTT, "<");

    // UI Elements
    // createButton("<", 16, 540, clickBackButton); // Back


    backButton = createUI(backTexture,
                          backTexture,
                          backTexture,
                          (SDL_Color) {255, 240, 220},
                          (SDL_Color) {211, 44, 44},
                          (SDL_Color) {255, 240, 220},
                          16,
                          550,
                          clickBackButton,
                          NULL); // Fullscreen

    fullscreenToggle = createUI(unchecked,
                                checked,
                                checked,
                                (SDL_Color) {255, 240, 220},
                                (SDL_Color) {229, 229, 26},
                                (SDL_Color) {44, 210, 211},
                                200,
                                300,
                                toggleFullscreen,
                                NULL); // Fullscreen

    musicToggle = createUI(unchecked,
                           checked,
                           checked,
                           (SDL_Color) {255, 240, 220},
                           (SDL_Color) {229, 229, 26},
                           (SDL_Color) {44, 210, 211},
                           200,
                           376,
                           toggleMusic,
                           NULL); // Music

    filmToggle = createUI(unchecked,
                          checked,
                          checked,
                          (SDL_Color) {255, 240, 220},
                          (SDL_Color) {229, 229, 26},
                          (SDL_Color) {44, 210, 211},
                          200,
                          452,
                          toggleFilm,
                          NULL); // Music

    // Set UI State
    if (app.options.fullscreen == 1) {
        fullscreenToggle->isActive = 1;
    }
    if (app.options.musicEnabled == 1) {
        musicToggle->isActive = 1;
    }
    if (app.options.enableFilm == 1) {
        filmToggle->isActive = 1;
    }
}

static void logic(void) {
    doButtons();
    doUI(fullscreenToggle);
    doUI(musicToggle);
    doUI(filmToggle);
    doUI(backButton);
}

static void doButtons() {
    Button *b, *prev;

    prev = &stage.buttonsHead;
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    for (b = stage.buttonsHead.next; b != NULL; b = b->next) {
        // check if button clicked
        SDL_Rect rect = {b->rect.x, b->rect.y, b->rect.w, b->rect.h};
        if (SDL_PointInRect(&mouse, &rect) == SDL_TRUE) {
            b->isHover = 1;
            if (app.clicked) {
                b->onClick();
            }
        } else {
            b->isHover = 0;
        }

        prev = b;
    }
}

static void doUI(UI *ui) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    ui->isHover = 0;
    if (SDL_PointInRect(&mouse, &ui->rect) == SDL_TRUE) {
        ui->isHover = 1;
        if (app.clicked) {
            ui->onClick();
        }
    }
}

static void clickBackButton(void) {
    deinitOptions();
    initMenu();
}

static void toggleFullscreen(void) {
    if (app.options.fullscreen == 0) {
        if (!SDL_SetWindowFullscreen(app.window, SDL_WINDOW_FULLSCREEN)) {
            printf("Failed to set fullscreen: %s\n", SDL_GetError());
        }
        app.options.fullscreen = 1;
        fullscreenToggle->isActive = 1;
    } else {
        if (!SDL_SetWindowFullscreen(app.window, 0)) {
            printf("Failed to set fullscreen: %s\n", SDL_GetError());
        }
        app.options.fullscreen = 0;
        fullscreenToggle->isActive = 0;
        SDL_SetWindowSize(app.window, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

static void toggleMusic(void) {
    if (app.options.musicEnabled == 1) {
        app.options.musicEnabled = 0;
        musicToggle->isActive = 0;
        stopMusic();
    } else {
        app.options.musicEnabled = 1;
        musicToggle->isActive = 1;
        playMusic(1);
    }
}

static void toggleFilm(void) {
    if (app.options.enableFilm == 1) {
        app.options.enableFilm = 0;
        filmToggle->isActive = 0;
    } else {
        app.options.enableFilm = 1;
        filmToggle->isActive = 1;
    }
}

static void draw(void) {
    drawTextCenter(FNT_HEAD, app.screenW / 2, 72, "OPTIONS");

    drawButtons();

    drawUI(fullscreenToggle);
    drawText(FNT_BUTT, 276, 304, "Fullscreen");

    drawUI(musicToggle);
    drawText(FNT_BUTT, 276, 380, "Enable Music");

    drawUI(filmToggle);
    drawText(FNT_BUTT, 276, 456, "Enable Film Effect");

    drawUI(backButton);
}

static void drawButtons(void) {
    Button *b, *prev;
    for (b = stage.buttonsHead.next; b != NULL; b = b->next) {
        if (b->isHover == 1) {
            blit(b->hover, b->rect.x, b->rect.y);
        } else {
            blit(b->normal, b->rect.x, b->rect.y);
        }
    }
}

static void drawUI(UI *ui) {
    SDL_Texture *tex = ui->texNormal;
    SDL_Color col = ui->colNormal;
    if (ui->isHover) {
        col = ui->colHover;
        if (ui->texHover != NULL) {
            tex = ui->texHover;
        }
    }
    if (ui->isActive) {
        col = ui->colActive;
        if (ui->texActive != NULL) {
            tex = ui->texActive;
        }
    }
    SDL_SetTextureColorMod(tex, col.r, col.g, col.b);
    blit(tex, ui->rect.x, ui->rect.y);
}

static void createButton(char *str, int x, int y, void (*onClick)()) {
    Button *button = malloc(sizeof(Button));
    memset(button, 0, sizeof(Button));

    button->normal = textTexture(FNT_BUTT, str);
    button->hover = button->normal;
    SDL_Rect rect = {x, y, 0, 0};
    SDL_QueryTexture(button->normal, NULL, NULL, &rect.w, &rect.h);
    button->rect = rect;
    button->onClick = onClick;

    button->next = NULL;
    stage.buttonsTail->next = button;
    stage.buttonsTail = button;
}

static UI *createUI(SDL_Texture *texNormal,
                    SDL_Texture *texHover,
                    SDL_Texture *texActive,
                    SDL_Color colNormal,
                    SDL_Color colHover,
                    SDL_Color colActive,
                    int x,
                    int y,
                    void(*onClick)(),
                    void(*onDrag)()) {
    UI *ui = malloc(sizeof(UI));
    memset(ui, 0, sizeof(UI));

    ui->texNormal = texNormal;
    ui->texHover = texHover;
    ui->texActive = texActive;
    ui->colNormal = colNormal;
    ui->colHover = colHover;
    ui->colActive = colActive;

    SDL_Rect rect = {x, y, 0, 0};
    SDL_QueryTexture(ui->texNormal, NULL, NULL, &rect.w, &rect.h);
    ui->rect = rect;
    ui->onClick = onClick;
    ui->onDrag = onDrag;

    return ui;
}

static void deinitOptions(void) {
    Button *b;
    while (stage.buttonsHead.next) {
        b = stage.buttonsHead.next;
        stage.buttonsHead.next = b->next;
        if (b->normal != NULL) {
            SDL_DestroyTexture(b->normal);
            b->normal = NULL;
        }
        if (b->hover != NULL) {
            SDL_DestroyTexture(b->hover);
            b->hover = NULL;
        }
        free(b);
    }

    SDL_DestroyTexture(checked);
    SDL_DestroyTexture(unchecked);
    SDL_DestroyTexture(backTexture);

    free(backButton);
    free(fullscreenToggle);
    free(musicToggle);
    free(filmToggle);
}