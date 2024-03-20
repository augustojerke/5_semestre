public class Carro {
    private String nome;
    private String fabricante;
    private String placa;
    private int ano;
    private String cor;

    public Carro(String n, String f, String p, int a, String c) {
        nome = n;Shadow
        fabricante = f;
        placa = p;
        ano = a;
        cor = c;
    }

    public String getNome() { return nome; }
    public String getFabricante() { return fabricante; }
    public String getPlaca() { return placa; }
    public int getAno() { return ano; }
    public String getCor() { return cor; }
}
