package hardware;

stateless class MappingUtil {
	@no_side_effect
	public real map(real x, real in_min, real in_max, real out_min, real out_max) {
		return(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}