# <center>SQL Homework 3</center>
## <center>202440012028 陈新安</center>

### 一、定义必要实体集及其属性
#### 1.1 实体集定义：
1. **学生**: 学生编号（<u>**studentId**</u>）、学生姓名（studentName）
2. **教师**: 教师编号（<u>**teacherId**</u>）、教师姓名（teacherName）
3. **课程**: 课程编号（<u>**courseId**</u>）、课程名称（courseName）
4. **开课班**开课班号（<u>**classId**</u>）、课程编号（***courseId***）、年份（year）、学期（semester）
5. **教室**: 教室编号（<u>**roomId**</u>）、教室容量（capacity）
6. **考试**: 考试编号（<u>**examId**</u>）、课程编号（***courseId***）、考试日期（examDate）、考试时间（examTime）


#### 1.2 联系集定义：
1. **选课**：学生实体集与开课班实体集之间的多对多联系。一个学生可以选修多门课，一个开课班也可以有多个学生选修。该联系集无联系属性。
2. **开课**：课程实体集与开课班实体集之间的一对多联系。一个课程可以有多个教学班，但每个教学班只能对应一门课程。该联系集无联系属性。
3. **考试排期**：开课班实体集与学生实体集的聚合与考试实体集之间的一对一联系。一个开课班只有一场考试，每场考试只能对应一门课程。
4. **考场指派**：考试实体集与教室实体集之间的多对多联系。一场考试可以安排在多个教室进行，一间教室也可以安排多场考试。该联系集无联系属性。
5. **监考**：考试实体集与教师实体集之间的多对多联系。一个考试可以有多个监考教师，一个教师也可以监考多个考试。该联系集有一个属性：是否为主监考（isChief）。
6. **座位分配**：考试实体集和教室实体集的聚合 与 学生实体集之间的多对多联系。一个考试可以有多个学生参加，一个学生也可以参加多个考试。该联系集有一个属性：座位号（seatNo）。


### 二、E-R模型
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\4.1.png " width="600"/>
    <strong>图1：E-R模型简图</strong>
  </div>
</div>

---

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\4.2.png " width="600"/>
    <strong>图2：E-R模型详细图</strong>
  </div>
</div>

### 三、关系数据库模式
1. 学生Student(<u>**studentId**</u>, studentName)
2. 教师Teacher(<u>**teacherId**</u>, teacherName)
3. 课程Course(<u>**courseId**</u>, courseName)
4. 开课班Class(<u>**classId**</u>, courseId, year, semester,***courseId***)
5. 教室Room(<u>**roomId**</u>, capacity)
6. 考试Exam(<u>**examId**</u>, courseId, examDate, examTime)
7. 选课Enrollment(<u>***studentId***, ***classId***</u>,)
8. 开课Offering(<u>***courseId***, ***classId***</u>,)
9. 考试排期ExamSchedule(<u>***examId***</u>, ***classId***)
10. 考场指派ExamRoomAssignment(<u>***examId***, ***roomId***</u>)
11. 监考ExamProctoring(<u>***examId***, ***teacherId***</u>, isChief)
12. 座位分配SeatAssignment(<u>***examId***, ***roomId***, ***studentId***</u>, seatNo)