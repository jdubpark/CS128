/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Student {
    pub name: String,
    pub netid: String,
    pub schedule: Schedule,
}

/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Class {
    pub name: String,
    pub credit_hours: u8,
}

/// [DO NOT CHANGE THE STRUCT SIGNATURE]
#[derive(Debug, Clone, PartialEq)]
pub struct Schedule {
    pub classes: Vec<Class>,
    pub credit_hours: u8,
}

impl Student {
    /// Initialize a new student
    /// Set the students schedule with a new empty schedule
    pub fn new(name: String, netid: String) -> Student {
        let classes = vec![];
        let credit_hours = 0;
        let schedule = Schedule{classes, credit_hours};
        Student{name, netid, schedule}
    }

    /// Enroll a student in a schedule
    pub fn schedule_enrollment(&mut self, schedule: Schedule) {
        self.schedule = schedule;
    }

    // TODO: Implement this function
    /// Check if a student is a classmate of another student
    pub fn is_classmate(&self, other: &Student) -> bool {
        let self_classes: Vec<Class> = self.schedule.classes.clone();
        let other_classes: Vec<Class> = other.schedule.classes.clone();
        for class in self_classes.iter() {
            if other_classes.contains(class) {
                return true;
            }
        }
        false
    }
}

impl Class {
    /// Initialize a new class
    pub fn new(name: String, credit_hours: u8) -> Class {
        Class{name, credit_hours}
    }
}

impl Schedule {
    /// Initialize a new schedule
    /// Credit hours should be total up from the classes
    pub fn new(classes: Vec<Class>) -> Schedule {
        let mut credit_hours: u8 = 0;
        for class in classes.iter() {
            credit_hours += class.credit_hours;
        }
        Schedule{classes, credit_hours}
    }
}