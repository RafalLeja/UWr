public class Student {
  UsosWebPage usosWebPage; 
  usosWebPage.show();
}

public class UsosWebPage {
  GradeController gradeController;
  public void show() {
    pageLayout = gradeController.getStudentGradeInfo();
  }
}

public class GradeController {
  Student student;
  Course course;
  public PageLayout getStudentGradeInfo() {
    courses = student.getCourse()
    for (course in courses) {
      mark = course.getMark(student);
    }
    return new PageLayout();
  }
}

public class Course {
  List<Student> students;
  List<Mark> marks;
  public Mark getMark(Student student) {
    int out = getValue();
    return out;
  }
}

// Nie