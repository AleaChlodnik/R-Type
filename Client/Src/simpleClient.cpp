#include <netCommon.hpp>
#include <netMessage.hpp>
#include <netClient.hpp>

enum class CustomMsgTypes: uint32_t {
    FireBullet,
    MovePlayer
};

class CustomClient: public olc::net::ClientInterface<CustomMsgTypes> {
public:
    bool FireBullet(float x, float y) {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::FireBullet;
        msg << x << y;
        Send(msg);
    }
}

void simpleClient() {
    CustomClient c;
    c.Connect("127.0.0.1", 80);
    c.FireBullet(2.0f, 5.0f);
}
