
void enterElevator(int p) {
	original(p);
	weight = weight + getWeight(p);
}
void leaveElevator(int p) {
	original(p);
	weight = weight - getWeight(p);
}


