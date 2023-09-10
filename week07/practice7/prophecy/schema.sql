CREATE TABLE students (
    id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    house_name TEXT,
    house_head TEXT,
    PRIMARY KEY(house_name)
);

CREATE TABLE assignments (
    student_id INTEGER,
    student_name TEXT,
    student_house TEXT,
    FOREIGN KEY(student_id) REFERENCES students(id)
);