import java.util.HashMap;

public class StringBraile {
    private String texto;
    private HashMap<Character, String> listaBraile;

    public StringBraile(String texto){
        this.texto = texto;
        this.listaBraile = new HashMap<>();
        this.inicializarBrailes();
    }

    public void toStringBraile(){
        String linha1 = new String("");
        String linha2 = new String("");
        String linha3 = new String("");

        char[] vetor = new char[this.texto.length()];
        vetor = texto.toCharArray();

        for(int i = 0; i< vetor.length; i++){
            char caracterAtual = vetor[i];
            if(Character.isUpperCase(caracterAtual)) {
                linha1 += ". .  ";
                linha2 += ". .  ";
                linha3 += ". X  ";
                caracterAtual = Character.toLowerCase(caracterAtual);
            }
            if(Character.isDigit(caracterAtual)) {
                linha1 += ". X  ";
                linha2 += ". X  ";
                linha3 += "X X  ";
                caracterAtual = this.trocaNumeroPorLetra(caracterAtual);
            }
            if(caracterAtual == ' ') {
                linha1 += ". .  ";
                linha2 += ". .  ";
                linha3 += ". .  ";
                continue;
            }
            String letraBraile = this.retornaLetraBraile(caracterAtual);
            linha1 += letraBraile.substring(0,2) + "  ";
            linha2 += letraBraile.substring(2,4) + "  ";
            linha3 += letraBraile.substring(4,6) + "  ";
        }
        System.out.println(linha1);
        System.out.println(linha2);
        System.out.println(linha3);
    }

    public String retornaLetraBraile(char letra){
        return this.listaBraile.get(letra);
    }

    public char trocaNumeroPorLetra (char c){
        switch (c){
            case '1': return 'a';
            case '2': return 'b';
            case '3': return 'c';
            case '4': return 'd';
            case '5': return 'e';
            case '6': return 'f';
            case '7': return 'g';
            case '8': return 'h';
            case '9': return 'i';
            case '0': return 'j';
            default: return 'a';
        }
    }

    public void inicializarBrailes(){
        listaBraile.put('a', "X.....");
        listaBraile.put('b', "X.X...");
        listaBraile.put('c', "XX....");
        listaBraile.put('d', "XX.X..");
        listaBraile.put('e', "X..X..");
        listaBraile.put('f', "XXX...");
        listaBraile.put('g', "XXXX..");
        listaBraile.put('h', "X.XX..");
        listaBraile.put('i', ".XX...");
        listaBraile.put('j', ".XXX..");
        listaBraile.put('k', "X...X.");
        listaBraile.put('l', "X.X.X.");
        listaBraile.put('m', "XX..X.");
        listaBraile.put('n', "XX.XX.");
        listaBraile.put('o', "X..XX.");
        listaBraile.put('p', "XXX.X.");
        listaBraile.put('q', "XXXXX.");
        listaBraile.put('r', "X.XXX.");
        listaBraile.put('s', ".XX.X.");
        listaBraile.put('t', ".XXXX.");
        listaBraile.put('u', "X...XX");
        listaBraile.put('v', "X.X.XX");
        listaBraile.put('w', ".XXXX.");
        listaBraile.put('x', "XX..XX");
        listaBraile.put('y', "XX.XXX");
        listaBraile.put('z', "X..XXX");
    }
}
