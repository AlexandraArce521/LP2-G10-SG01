public class Personaje {
    
    private String nombre;
    private double vida;
    private String rol;   // Ya no es static
    
    private static final double ATAQUE_BASE = 10.0;   // Constante
    
    public Personaje(String nombre, String rol) {
        this.nombre = nombre;
        this.rol = rol;
        this.vida = 100; // Vida inicial por defecto
    }
    
    public String getNombre() {
        return nombre;
    }
    
    public void setNombre(String nombre) {
        this.nombre = nombre;
    }
    
    public double getVida() {
        return vida;
    }
    
    public void setVida(double vida) {
        if (vida <= 0) {
            this.vida = 0;
            System.out.println("(!) Perdió. No tiene vida");
        } else {
            this.vida = vida;
        }
    }
    
    public String getRol() {
        return rol;
    }
    
    public void setRol(String rol) {
        this.rol = rol;
    }
    
    public static double getAtaqueBase() {
        return ATAQUE_BASE;
    }

    public void atacar(Personaje objetivo) {
        System.out.println(nombre + " ataca a " + objetivo.getNombre() + " causando " + ATAQUE_BASE + " de daño.");
        objetivo.setVida(objetivo.getVida() - ATAQUE_BASE);
        System.out.println("Vida restante de " + objetivo.getNombre() + ": " + objetivo.getVida());
    }
    
}
