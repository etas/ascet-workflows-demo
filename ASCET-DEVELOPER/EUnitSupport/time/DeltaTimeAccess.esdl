package time;

/**
 * Service class that allows access to the globally defined @dT variable. 
 *
 * While it is prohibited to change the value of this variable in ESDL models, it is
 * helpful to do so in unit tests. This class provides methods to read and even write
 * the @dT variable.
 */
stateless class DeltaTimeAccess {
    /*
     * Gets the current value of the @dT variable.
     */
    @symbol("ASCET_GET_MODEL_DT")
    public extern real getDeltaTime();

    /*
     * Updates the value of the @dT variable setting it to 'value'.
     */
    @symbol("ASCET_SET_MODEL_DT") 
    public extern void setDeltaTime(real value);
}