package HomeWork.PTA.P8;

public class Pupil extends Person{
    private String school;

    public String getSchool() {
        return school;
    }

    public void setSchool(String school) {
        this.school = school;
    }

    public Pupil(String school) {
        this.school = school;
    }

    public Pupil() {
    }
}
