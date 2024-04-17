public class ClockDisplay {
    private NumberDisplay hours;
    private NumberDisplay minutes;
    private String displayString;

    public ClockDisplay(){
        hours = new NumberDisplay(24);
        minutes = new NumberDisplay(60);
        updateDisplay();
    }

    public ClockDisplay(int h, int m){
        hours = new NumberDisplay(24, h);
        minutes = new NumberDisplay(60, m);
        updateDisplay();
    }

    public void timeTick(){
        minutes.increment();
        if(minutes.getValue() == 0){
            hours.increment();
        }
        updateDisplay();
    }

    private void updateDisplay(){
        displayString = hours.getDisplayValue() + ":" +
            minutes.getDisplayValue();
    }

    public String getDisplayString(){
        return displayString;
    }''
}
