/* appearance */
static unsigned int borderpx = 1;      /* border pixel of windows */
static unsigned int snap = 5;         /* snap pixel */
static const unsigned int gappih = 20; /* horiz inner gap between windows */
static const unsigned int gappiv = 20; /* vert inner gap between windows */
static const unsigned int gappoh =
    20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    30; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int swallowfloating =
    0;                  /* 1 means swallow floating windows by default */
static int showbar = 1; /* 0 means no bar */
static const int showtitle = 1;    /* 0 means no title */
static const int showtags = 1;     /* 0 means no tags */
static const int showlayout = 1;   /* 0 means no layout indicator */
static const int showstatus = 1;   /* 0 means no status bar */
static const int showfloating = 0; /* 0 means no floating indicator */
static int topbar = 1;             /* 0 means bottom bar */
static char dmenufont[] = "Iosevka Nerd Font:size=12";
static const char *fonts[] = {
    "Iosevka Nerd Font:size=12",
    "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true"
};

/* default colors used if xrdb is not loaded */

static char normbgcolor[] = "#1f1c14";
static char normbordercolor[] = "#1f1c14";
static char normfgcolor[] = "#B5976E";
static char selfgcolor[] = "#1f1c14";
static char selbordercolor[] = "#928c82";
static char selbgcolor[] = "#B5976E";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel]  = {selbgcolor,  selfgcolor,  selbordercolor},
    /* for bar --> {text, background, null} */
    [SchemeStatus]   = {normfgcolor,   normbgcolor, normbgcolor}, /* status R */
    [SchemeTagsSel]  = {normfgcolor,   normbgcolor, normbgcolor}, /* tag L sel */
    [SchemeTagsNorm] = {selbordercolor, normbgcolor, normbgcolor},/* tag L unsel */
    [SchemeInfoSel]  = {normfgcolor,   normbgcolor, normbgcolor}, /* info M sel */
    [SchemeInfoNorm] = {normfgcolor,   normbgcolor, normbgcolor}, /* info M unsel */
};

/* tagging */

static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
// static const char *tags[] = { "󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳",
// "󰎶", "󰎹", "󰎼" };
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
     /* class     instance  title           tags mask  isfloating  isterminal
        noswallow  monitor */
    {"neofetch", NULL, "Welcome",   0, 1, 1, 0, -1},     /* neofetch startup window (must be before general St rule) */
    {"st-256color", NULL, NULL,        0, 0, 1, 0, -1},
    {"fzfmenu",NULL, NULL,        0, 1, 1, 1, -1},     /* fzf menu (any title) */
    {"mpv",    NULL, NULL,        0, 1, 0, 1, -1},     /* mpv video player */
    {"Nsxiv",  NULL, NULL,        0, 1, 0, 1, -1},     /* nsxiv image preview */
    {NULL,      NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
    {"floating_calc", NULL,      NULL,       0,            1,           -1 },
    {"musicwiki",    "musicwiki",  NULL,       0,            1,           -1 },
    {"floating_script",  NULL,       NULL,       0,            1,           -1 },
};

#include "vanitygaps.c"

/* XF86 media key symbols */

#include <X11/XF86keysym.h>
/* layout(s) */

static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    0; /* 1 will force focus on the fullscreen window */
static const Layout layouts[] = {
    /* alt glyphs: 󱡗 󱏋 */
    /* symbol     arrange function */
    {"",   tile},    /* first entry is default */
    {"󰇥", NULL},      /* no layout function means floating behavior */
    {"", monocle},
    {"󰫣", spiral},
    {"󰫥", dwindle},
    {"λ",   tile}, // BACKUP OF FIRST TILE, SWAPPED FOR GALAXY
    {"",   tile},  // BACKUP 2
};

/* key definitions */

#define MODKEY Mod4Mask // windows key
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } // DEFINES FOR $HOME COMAND
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_j, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD,                                                                    \
       XK_k,                                                                   \
       ACTION##stack,                                                          \
       {.i = INC(-1)}}, /*{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } },   \
                        { MOD, XK_q,     ACTION##stack, {.i = 0 } },           \
                        { MOD, XK_a,     ACTION##stack, {.i = 1 } },           \
                        { MOD, XK_z,     ACTION##stack, {.i = 2 } },           \
                        { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */
//* helper for spawning shell commands in the pre dwm-5.0 fashion */
//
//#define SHCMD(cmd)                                                             \
//  {                                                                            \
//    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
//  }
//* helper for launching gtk application */

#define GTKCMD(cmd)                                                            \
  {                                                                            \
    .v = (const char *[]) { "/usr/bin/gtk-launch", cmd, NULL }                 \
  }
#define STATUSBAR "dwmblocks"
#define BROWSER   "helium-browser"
#define CHATCLIENT "discord"

/* commands */

static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,       "-fn",
                                 dmenufont,   "-nb", normbgcolor,    "-nf",
                                 normfgcolor, "-sb", selbordercolor, "-sf",
                                 selfgcolor,  NULL};
static const char *termcmd[] = {"kitty", NULL};
static const Arg tagexec[] = {
    /* spawn application when tag is middle-clicked */
    {.v = termcmd}, /* 1 */
    {.v = termcmd}, /* 2 */
    {.v = termcmd}, /* 3 */
    {.v = termcmd}, /* 4 */
    {.v = termcmd}, /* 5 */
    {.v = termcmd}, /* 6 */
    {.v = termcmd}, /* 7 */
    {.v = termcmd}, /* 8 */
    {.v = termcmd}, /* 9 */
                    /* GTKCMD("gtkapplication") */
};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY,              XK_p,          spawn,            {.v = dmenucmd}},
    {MODKEY,              XK_Return,     spawn,            {.v = termcmd}},
    {MODKEY | ControlMask,  XK_b,        togglebar,        {0}},
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
    {MODKEY | ShiftMask,  XK_i,          incnmaster,       {.i = +1}}, /* more masters */
    {MODKEY | ControlMask,XK_i,          incnmaster,       {.i = -1}}, /* fewer masters */
    {MODKEY,              XK_h,          setmfact,         {.f = -0.05}},
    {MODKEY | ShiftMask,  XK_h,          setmfact,         {.f = +0.05}},
    {MODKEY,              XK_Tab,        view,             {0}},
    {MODKEY,              XK_0,          view,             {.ui = ~0}},
    {MODKEY | ShiftMask,  XK_0,          tag,              {.ui = ~0}},
    {MODKEY | ControlMask | ShiftMask, XK_q, quit,         {1}}, /* refresh dwm (restartsig) */
    {MODKEY | ShiftMask,  XK_BackSpace,  quit,             {0}}, /* quit dwm */
    {MODKEY,              XK_q,          killclient,       {0}}, /* quit window */
    {MODKEY | ShiftMask,  XK_q,          killclient,       {.ui = 1}}, /* kill others */
    /* { MODKEY|ShiftMask|ControlMask,  XK_q,  killclient, {.ui = 2} }, */
    {MODKEY | ControlMask,XK_x,          xrdb,             {.v = NULL}}, /* refresh xrdb colors */
    {MODKEY,              XK_t,          setlayout,        {.v = &layouts[0]}},
    {MODKEY,              XK_f,          togglefullscreen, {0}}, /* fullscreen */
    //{MODKEY | ControlMask | ShiftMask,  XK_m, setlayout,   {.v = &layouts[2]}}, /* monocle */
    //{MODKEY | ControlMask | ShiftMask,  XK_t, setlayout,   {.v = &layouts[3]}}, /* spiral */
    //{MODKEY | ShiftMask,  XK_t,          setlayout,        {.v = &layouts[4]}}, /* dwindle */
    {MODKEY | ControlMask,XK_space,      setlayout,        {0}},
    {MODKEY | ShiftMask,  XK_space,      togglefloating,   {0}},
    {MODKEY,              XK_space,      zoom,             {0}},
    {MODKEY | ControlMask,XK_space,      focusmaster,      {0}},
    {MODKEY | ControlMask | ShiftMask, XK_s, togglesticky, {0}},
    /* multi-monitor control */
    {MODKEY,              XK_bracketright, focusmon, {.i = -1}},
    {MODKEY | ShiftMask,  XK_bracketright, tagmon,   {.i = -1}},
    {MODKEY,              XK_bracketleft, focusmon,  {.i = +1}},
    {MODKEY | ShiftMask,            XK_bracketleft, tagmon,    {.i = +1}},
    /* gaps control */
    {MODKEY,                        XK_g,     incrgaps,       {.i = -3}}, /* all */
    {MODKEY | ShiftMask,            XK_g,     incrgaps,       {.i = +3}},
   // {MODKEY | Mod1Mask,             XK_minus, incrigaps,      {.i = +1}}, /* inner */
   // {MODKEY | Mod1Mask | ShiftMask, XK_equal, incrigaps,      {.i = -1}},
   // {MODKEY | Mod1Mask,             XK_o,     incrogaps,      {.i = +1}}, /* outer */
   // {MODKEY | Mod1Mask | ShiftMask, XK_o,     incrogaps,      {.i = -1}},
   // {MODKEY | Mod1Mask,             XK_6,     incrihgaps,     {.i = +1}}, /* inner horiz */
   // {MODKEY | Mod1Mask | ShiftMask, XK_6,     incrihgaps,     {.i = -1}},
   // {MODKEY | Mod1Mask,             XK_7,     incrivgaps,     {.i = +1}}, /* inner vert */
   // {MODKEY | Mod1Mask | ShiftMask, XK_7,     incrivgaps,     {.i = -1}},
   // {MODKEY | Mod1Mask,             XK_8,     incrohgaps,     {.i = +1}}, /* outer horiz */
   // {MODKEY | Mod1Mask | ShiftMask, XK_8,     incrohgaps,     {.i = -1}},
   // {MODKEY | Mod1Mask,             XK_9,     incrovgaps,     {.i = +1}}, /* outer vert */
   // {MODKEY | Mod1Mask | ShiftMask, XK_9,     incrovgaps,     {.i = -1}},
   // {MODKEY | ShiftMask,            XK_plus,  togglegaps,     {0}},
   // {MODKEY | ShiftMask,            XK_minus, defaultgaps,    {0}},
    /* tag keys */
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    /* toggle statusbar pieces individually */
    //{MODKEY | ControlMask,  XK_t,     togglebartitle,  {0}},  // NEVER UNCOMENT CRUCIAL FOR NAVIGATION
    {MODKEY | ControlMask,  XK_t,     togglebarstatus, {0}},
    //{MODKEY | ControlMask,  XK_t,     togglebartags,   {0}},  // NEVER UNCOMENT CRUCIAL FOR NAVIGATION
    {MODKEY | ControlMask,  XK_e,     togglebarcolor,  {0}}, /* swaps fg/bg */
    //{MODKEY | ControlMask,  XK_r,     togglebarlt,     {0}},  // NEVER UNCOMENT CRUCIAL LOOKS!
    {MODKEY | ControlMask,  XK_f,     togglebarfloat,  {0}},
    /* application bindings */
    {MODKEY | ShiftMask,    XK_m,     spawn, {.v = (const char *[]) {"kitty", "-e", "nmtui", NULL}}}, // NETWORK MANAGER
    {MODKEY,                XK_m,     spawn, {.v = (const char *[]) {"kitty", "-e", "rmpc", NULL}}}, // MUSIC PLAYER
    {MODKEY | ControlMask,  XK_m,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/app-players/movplayer", NULL}}}, // MOVIE PLAYER
    {MODKEY | ControlMask | ShiftMask, XK_m, spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/app-players/movie-installer", NULL}}}, // MOVIE INSTALLER
    {MODKEY,                XK_a,     spawn, {.v = (const char *[]) {"kitty", "-e", "sh", "-c", "ani-cli --dub --skip", NULL}}}, // ANIME PLAYER
    {MODKEY,                XK_b,     spawn, {.v = (const char *[]) {BROWSER, NULL}}}, // BROWSER
    {MODKEY,                XK_d,     spawn, {.v = (const char *[]) {CHATCLIENT, NULL}}}, // DISCORD
    {MODKEY | ShiftMask,    XK_d,     spawn, {.v = (const char *[]) {"/bin/bash", "/home/atego/dotfiles/scripts/.config/scripts/app-players/yt-music-tool", NULL}}}, // MUSIC DOWNLOADER
    {MODKEY | ShiftMask,    XK_f,     spawn, {.v = (const char *[]) {"nautilus", NULL}}}, // nautilus
    {MODKEY | ShiftMask,    XK_b,     spawn, {.v = (const char *[]) {"kitty", "-e", "btop", NULL}}}, // STATISTICS SCREEN
    {MODKEY | ControlMask,  XK_c,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/audio-video/selective-webm-convertion", NULL}}}, // CONVERT VIDEOS TO LOW QUALITY WEBM
    {MODKEY,                XK_c,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/custom-helpers/cal-check", NULL}}}, // MANUALY CHECK CALLENDAR FOR TODAY AND TMRW
    {MODKEY | ShiftMask,    XK_c,     spawn, {.v = (const char *[]) {"kitty", "-e", "/home/atego/dotfiles/scripts/.config/scripts/custom-helpers/cheat.sh", NULL}}}, // COMAND CHEAT SHEET
    {MODKEY,                XK_n,     spawn, {.v = (const char *[]) {"kitty", "-e", "nvim", NULL}}}, // NVIM
    {MODKEY | ShiftMask,    XK_n,     spawn, {.v = (const char *[]) {"kitty", "-e", "/home/atego/dotfiles/scripts/.config/scripts/custom-helpers/notes.sh", NULL}}}, // NOTES
    {MODKEY,                XK_e,     spawn, {.v = (const char *[]) {"emacs", NULL}}}, // EMACS
    {MODKEY,                XK_y,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/app-players/ytplay-launcher", NULL}}},  // YOUTUBE PLAYER
    {MODKEY | ControlMask,  XK_a,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/audio-video/audiorecording", "toggle", NULL}}}, // AUDIO RECORDER
    {MODKEY | ShiftMask,    XK_r,     spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/audio-video/screenrecord", "toggle", NULL}}}, // SCREEN RECORD
    {MODKEY,                XK_s,     spawn, {.v = (const char *[]) {"steam", NULL}}}, // STEAM
    {MODKEY | ShiftMask,    XK_w,     spawn, {.v = (const char *[]) {"kitty", "-e", "/home/atego/dotfiles/scripts/.config/scripts/images-photos-wallpapers/wal-picker.sh", NULL}}}, // WALLPAPER PICKER
    {MODKEY,                XK_w,     spawn, {.v = (const char *[]) {"onlyoffice-desktopeditors", NULL}}}, // MS OFFICE
    {MODKEY | ControlMask | ShiftMask, XK_c, spawn, {.v = (const char *[]) {"/opt/snapchat-nativefier/Snapchat", "--no-sandbox", NULL}}}, // SNAP
    /* ThinkPad media keys (F1-F4): F1=mute, F2=vol-, F3=vol+, F4=mic-mute */
    {0, XF86XK_AudioMute,             spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+10 dwmblocks")},
    {0, XF86XK_AudioLowerVolume,      spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+10 dwmblocks")},
    {0, XF86XK_AudioRaiseVolume,      spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+10 dwmblocks")},
    {0, XF86XK_AudioMicMute,          spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle; pkill -RTMIN+10 dwmblocks")},
    /* Extra F11 etc. keys */
    {0, XF86XK_Tools,                 spawn, SHCMD("kitty -e rmpc") },
    {0, XF86XK_AudioStop,             spawn, SHCMD("mpc stop; pkill -RTMIN+11 dwmblocks") },
    {0, XF86XK_AudioPrev,             spawn, SHCMD("mpc prev; pkill -RTMIN+11 dwmblocks") },
    {0, XF86XK_AudioPlay,             spawn, SHCMD("mpc toggle; pkill -RTMIN+11 dwmblocks") },
    {0, XF86XK_AudioNext,             spawn, SHCMD("mpc next; pkill -RTMIN+11 dwmblocks") },
    {0, XF86XK_Mail,                  spawn, SHCMD("helium-browser https://mail.google.com") },
    {0, XF86XK_HomePage,              spawn, SHCMD("kitty --class floating_script --title Powermenu --override initial_window_width=600 --override initial_window_height=400 -e /home/atego/dotfiles/scripts/.config/scripts/system/powermenu") },
    {0, XF86XK_Calculator,            spawn, {.v = (const char *[]) {"kitty", "--class", "floating_calc", "--title", "Calculator", "--override", "initial_window_width=800", "--override", "initial_window_height=450", "-e", "/home/atego/dotfiles/scripts/.config/scripts/app-players/calculator.py", NULL } } },
    /* brightness keys */
    {0, XF86XK_MonBrightnessUp,       spawn, SHCMD("brightnessctl set +1%")},
    {0, XF86XK_MonBrightnessDown,     spawn, SHCMD("brightnessctl set 1%-")},
    /* screenshot binds */
    {MODKEY | ShiftMask,               XK_s,  spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/images-photos-wallpapers/screenshot-minimal.sh", NULL}}}, // SCREENSHOT
    {MODKEY | ControlMask,             XK_s,  spawn, {.v = (const char *[]) {"/home/atego/dotfiles/scripts/.config/scripts/images-photos-wallpapers/screenshot.sh", NULL}}}, // SPECIFIC SCREENSHOT
};

/* button definitions */

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
/* click                event mask           button          function argument */

#ifndef __OpenBSD__
    {ClkWinTitle,  0,          Button2,        zoom,         {0}},
    {ClkStatusText,0,          Button1,        sigstatusbar, {.i = 1}},
    {ClkStatusText,0,          Button2,        sigstatusbar, {.i = 2}},
    {ClkStatusText,0,          Button3,        sigstatusbar, {.i = 3}},
    {ClkStatusText,0,          Button4,        sigstatusbar, {.i = 4}},
    {ClkStatusText,0,          Button5,        sigstatusbar, {.i = 5}},
    {ClkStatusText,ShiftMask,  Button1,        sigstatusbar, {.i = 6}},
#endif
    {ClkStatusText,ShiftMask,  Button3,        spawn,
     SHCMD("st -e nvim ~/.local/src/dwmblocks/blocks.h")},
    {ClkClientWin, MODKEY,     Button1,        movemouse,    {0}},      /* left */
    {ClkClientWin, MODKEY,     Button2,        defaultgaps,  {0}},      /* middle */
    {ClkClientWin, MODKEY,     Button3,        resizemouse,  {0}},      /* right */
    {ClkClientWin, MODKEY,     Button4,        incrgaps,     {.i = +1}},/* scroll up */
    {ClkClientWin, MODKEY,     Button5,        incrgaps,     {.i = -1}},/* scroll down */
    {ClkTagBar,    0,          Button1,        view,         {0}},
    {ClkTagBar,    0,          Button3,        toggleview,   {0}},
    {ClkTagBar,    MODKEY,     Button1,        tag,          {0}},
    {ClkTagBar,    MODKEY,     Button3,        toggletag,    {0}},
    {ClkRootWin,   0,          Button2,        togglebar,    {0}}, /* hide bar */
};
