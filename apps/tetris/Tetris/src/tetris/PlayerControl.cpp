#include "PlayerControl.h"



PlayerControl::PlayerControl()
{
}


PlayerControl::~PlayerControl()
{
}

void PlayerControl::setup(vector<shared_ptr<Paddle>> paddles_, GameParameters * params_)
{
	paddles = paddles_;
	params = params_;

}
