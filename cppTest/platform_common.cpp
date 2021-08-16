struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_UP_2,
	BUTTON_DOWN_2,
	//BUTTON_UPLEFT,
	//BUTTON_UPRIGHT,
	//BUTTON_DOWNLEFT,
	//BUTTON_DOWNRIGHT,

	BUTTON_COUNT, //should be the last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};