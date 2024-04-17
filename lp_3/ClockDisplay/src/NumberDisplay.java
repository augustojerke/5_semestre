public class NumberDisplay {
    private int limit;
    private int value;

    public NumberDisplay(int l, int v){
        limit = l;
        value = v;
    }

    public NumberDisplay(int l){
        limit = l;
        value = 0;
    }

    public void increment(){
        value = (value + 1) % limit;
    }

    public int getValue(){
        return value;
    }

    public String getDisplayValue(){
        if(value < 10)
            return "0" + value;
        return "" + value;
    }
}
