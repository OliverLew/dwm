/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static int gappx              = 16;       /* gaps between windows */
static int gapsingle          = 1;        /* gaps when there is only 1 window */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int barheightmin       = 24;       /* minimum height if > 0 */
static const char *fonts[]          = {
	"monospace:size=11:style=Medium",
	"JoyPixels:size=11",
	"Noto Sans CJK SC:size=11:style=Medium",
	"Material Design Icons:size=13"
};
static int barpaddingh        = 2;        /* horizontal padding for statusbar */
static int barpaddingtop      = 2;        /* top padding for statusbar */
static int barpaddingbottom   = 0;        /* bottom padding for statusbar */
static char foreground[]      = "#000000";
static char background[]      = "#ffffff";
static char color0[]          = "#000000";
static char color1[]          = "#AA0000";
static char color2[]          = "#00AA00";
static char color3[]          = "#AA5500";
static char color4[]          = "#0000AA";
static char color5[]          = "#AA00AA";
static char color6[]          = "#00AAAA";
static char color7[]          = "#AAAAAA";
static char color8[]          = "#555555";
static const char *base_colors[]    = {
	color0, color1, color2, color3,
	color4, color5, color6, color7, color8
};
static const char *colors[][3]      = {
	/*               fg          bg          border   */
	[SchemeNorm] = { foreground, background, color0 },
	[SchemeSel]  = { background, color6,     color6 },
 };

/* tagging */
static const char *tags[] = { "󰲡", "󰲣", "󰲥", "󰲧", "󰲩" };
static const char *tags_busy[] = { "󰲠", "󰲢", "󰲤", "󰲦", "󰲨" };
static const char *tags_curr[] = { "󰓏", "󰓏", "󰓏", "󰓏", "󰓏" };

static const Rule rules[] = {
	/* class      instance    title    tags     center   float    sticky   monitor */
	{ "firefox",  NULL,       NULL,    1 << 1,  0,       0,       0,       -1 },
	{ "firefox",  "Toolkit",  NULL,    1 << 1,  0,       1,       1,       -1 },
	{ "firefox",  "Browser",  NULL,    1 << 1,  1,       1,       0,       -1 },
	{ "Arandr",   NULL,       NULL,    0,       1,       1,       0,       -1 },
	{ "Peek",     NULL,       NULL,    0,       1,       1,       0,       -1 },
	{ "floating", NULL,       NULL,    0,       1,       1,       0,       -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰙀",      tile },    /* first entry is default */
	{ "󰄮",      monocle },
	{ "󰕰",      grid },
	{ "󰕬",      centeredmaster },
	{ "󰕕",      NULL },    /* no layout function means floating behavior */
};

/* These symbols will replace the monocle symbol with corresponding client count */
static const char *monocle_n[] = { "󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶", "󰎹", "󰎼", "󰎿" };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static char *statuscmds[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };
static char *statuscmd[] = { "dwm-status", NULL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "borderpx",           INTEGER, &borderpx },
		{ "gappx",              INTEGER, &gappx },
		{ "gapsingle",          INTEGER, &gapsingle },
		{ "snap",               INTEGER, &snap },
		{ "showbar",            INTEGER, &showbar },
		{ "topbar",             INTEGER, &topbar },
		{ "barheight",          INTEGER, &barheightmin },
		{ "foreground",         STRING,  &foreground },
		{ "background",         STRING,  &background },
		{ "color0",             STRING,  &color0 },
		{ "color1",             STRING,  &color1 },
		{ "color2",             STRING,  &color2 },
		{ "color3",             STRING,  &color3 },
		{ "color4",             STRING,  &color4 },
		{ "color5",             STRING,  &color5 },
		{ "color6",             STRING,  &color6 },
		{ "color7",             STRING,  &color7 },
		{ "color8",             STRING,  &color8 },
		{ "nmaster",            INTEGER, &nmaster },
		{ "resizehints",        INTEGER, &resizehints },
		{ "mfact",              FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Escape, view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_6,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_7,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_8,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_9,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_period, shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_minus,  setgaps,        {.i = -24 } },
	{ MODKEY|ControlMask,           XK_equal,  setgaps,        {.i = +24 } },
	{ MODKEY|ControlMask,           XK_0,      setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1 } },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1 } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        tag,            {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      {.i = +1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,      {.i = -1 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

