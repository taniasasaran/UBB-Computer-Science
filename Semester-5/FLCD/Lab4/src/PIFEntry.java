public class PIFEntry {
    private String token;
    private Pair position;

    public PIFEntry(String token, Pair position) {
        this.token = token;
        this.position = position;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public Pair getPosition() {
        return position;
    }

    public void setPosition(Pair position) {
        this.position = position;
    }

    @Override
    public String toString() {
        return "(" + this.token + ", " + this.position + ")";
    }
}
