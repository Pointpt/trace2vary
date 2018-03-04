package MinePumpSystem;

public class Environment {
	boolean isHighWaterSensorDry() {
		return waterLevel != WaterLevelEnum.high;
	}
}
