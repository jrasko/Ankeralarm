
#ifndef ANKERALARM_5_0_TESTSTATE_H
#define ANKERALARM_5_0_TESTSTATE_H

#include "Utils.h"

class TestState : public State {
private:
	Position pos = Position(LatitudeDegree(50.592954),
							LongitudeDegree(7.0 + (20. / 60.) + (54. / 3600.)));
public:
	void getLCDOutput() override;
};

void TestState::getLCDOutput() {
	display->lcd.print("D");
	display->lcd.print(pos.distanceTo(display->props.myGPS.getCurrentPosition()));
	display->lcd.print(" S");
	display->lcd.print(display->props.myGPS.getSatellitesAvailable());
	display->lcd.setCursor(0, 1);
	display->lcd.print("Q");
	display->lcd.print(display->props.myGPS.getGPSQuality());
	display->lcd.print(" H");
	display->lcd.print(display->props.myGPS.getHDOP());
}

#endif //ANKERALARM_5_0_TESTSTATE_H
