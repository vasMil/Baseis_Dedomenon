DROP DATABASE IF EXISTS staff_evaluation;
CREATE DATABASE staff_evaluation;
USE staff_evaluation;

DROP TABLE IF EXISTS user;
CREATE TABLE user(
	username VARCHAR(12) NOT NULL UNIQUE,
    password VARCHAR(10) NOT NULL, #8a epitrepsoume 2 atoma na exoun ton idio kodiko
    name VARCHAR(25) NOT NULL,
    surname VARCHAR(35) NOT NULL,
    reg_date DATETIME DEFAULT CURRENT_TIMESTAMP, #should NOT be able to change #DEFAULT DOCUMENTATION:
    email VARCHAR(30) NOT NULL UNIQUE, #https://dev.mysql.com/doc/refman/8.0/en/timestamp-initialization.html
    UNIQUE(name, surname),
    PRIMARY KEY (username)
);

DROP TABLE IF EXISTS company;
CREATE TABLE company(
	afm CHAR(9) PRIMARY KEY,
    doy VARCHAR(15) NOT NULL,
    name VARCHAR(35) NOT NULL, #επιτρέπουμε 2 εταιρείες να έχουν την ίδια επωνυμία
    phone BIGINT(16) NOT NULL UNIQUE,
    street VARCHAR(15) NOT NULL, #not unique, 2 companies may be in the same building
    street_num INT(4) NOT NULL,
    city VARCHAR(15) NOT NULL,
    country VARCHAR(15) NOT NULL
);

DROP TABLE IF EXISTS manager;
CREATE TABLE manager(
	username VARCHAR(12) PRIMARY KEY, #PRIMARY KEY implies unique and not null
    exp_years TINYINT(4) NOT NULL,
    firm_afm CHAR(9) NOT NULL,
    FOREIGN KEY (firm_afm) REFERENCES company(afm)
    ON DELETE RESTRICT ON UPDATE CASCADE, #Should not be able to delete a firm if there are still managers working there,
    FOREIGN KEY (username) REFERENCES user(username) #on update the field should be updated aswell
    ON DELETE RESTRICT ON UPDATE RESTRICT
);
#Should not be able to delete a user, while there is a manager using the account,
#neither should be able to update the username, as it is clearly stated.
#Note that we may assign a foreign key as a primary key since it is a 1-1 relationship. Otherwise you should be using a manager id aswell

DROP TABLE IF EXISTS employee;
CREATE TABLE employee(
	am INT(4) NOT NULL AUTO_INCREMENT,
    username VARCHAR(12) NOT NULL UNIQUE,
    bio TEXT,
    certificates VARCHAR(35),
    awards VARCHAR(35),
    firm_afm CHAR(9) NOT NULL,
    exp_years TINYINT(4),
    PRIMARY KEY (am),
    FOREIGN KEY (username) REFERENCES user(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT,
    FOREIGN KEY (firm_afm) REFERENCES company(afm)
    ON DELETE RESTRICT ON UPDATE CASCADE
);

DROP TABLE IF EXISTS evaluator;
CREATE TABLE evaluator(
	username VARCHAR(12) NOT NULL,
    exp_years TINYINT(4) NOT NULL,
    firm_afm CHAR(9) NOT NULL,
    evaluator_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    FOREIGN KEY (username) REFERENCES user(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT,
    FOREIGN KEY (firm_afm) REFERENCES company(afm)
    ON DELETE RESTRICT ON UPDATE CASCADE
);

DROP TABLE IF EXISTS job;
CREATE TABLE job(
	job_id INT(4) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    start_date DATE NOT NULL,
    salary float(6,1) NOT NULL,
    position VARCHAR(40) NOT NULL,
    edra VARCHAR(45) NOT NULL,
    evaluator_username VARCHAR(12) NOT NULL,
    announce_date DATETIME NOT NULL,
    submission_date DATE NOT NULL,
    FOREIGN KEY (evaluator_username) REFERENCES evaluator(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS project;
CREATE TABLE project(
	project_id TINYINT (4) NOT NULL AUTO_INCREMENT,
	descr TEXT NOT NULL,
	url VARCHAR(60) NOT NULL UNIQUE,
	PRIMARY KEY (project_id)
);

DROP TABLE IF EXISTS  has_project;
CREATE TABLE has_project(
	project_id TINYINT(4) NOT NULL, #epitrepete 2 employees na exoun to idio project
    empl_proj_num TINYINT(4) NOT NULL DEFAULT 0, #gemizei mesa apo trigger
    username_empl VARCHAR(12) NOT NULL, #epitrepoume kapoios employee na exei 2 diaforetika project
    PRIMARY KEY (project_id, username_empl),
    FOREIGN KEY (project_id) REFERENCES project(project_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT,
    FOREIGN KEY (username_empl) REFERENCES employee(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS languages;
CREATE TABLE languages(
	empl_username VARCHAR(12) UNIQUE NOT NULL,
    lang SET ('EN','FR','SP','GR'),
    PRIMARY KEY (empl_username),
    FOREIGN KEY (empl_username) REFERENCES employee(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS subject;
CREATE TABLE subject(
	title VARCHAR(36) PRIMARY KEY,
    descr TINYTEXT NOT NULL,
    belongs_to VARCHAR(36) DEFAULT NULL,
    FOREIGN KEY (belongs_to) REFERENCES subject(title)
    ON DELETE SET NULL ON UPDATE CASCADE 
    #deleting the parent subject will not be affecting the current one, it will just be a lonely subject
	#maybe setting it to be equal with the parent of the deleted parent is wise -> fix it using a TRIGGER (den ylopoih8ike) 
);

DROP TABLE IF EXISTS job_requires;
CREATE TABLE job_requires(
	job_id INT(4) NOT NULL,
    sub_title VARCHAR(36) NOT NULL,
    PRIMARY KEY (job_id, sub_title),
    FOREIGN KEY (job_id) REFERENCES job(job_id)
    ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (sub_title) REFERENCES subject(title)
    ON DELETE RESTRICT ON UPDATE RESTRICT
#if a job is deleted then there is nothing to be required and if the job_id changes (which is unlikely)
#the requirements for the job shall not be dropped
#deleting a subject that is required for a job should not be allowed.
#Updating the subject may change the job_requirements when that is not what we wanted
);

DROP TABLE IF EXISTS report;
CREATE TABLE report(
	report_id INT(4) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    manager_username VARCHAR(12) NOT NULL,
    employee_username VARCHAR(12) NOT NULL,
    report_text TEXT, #will be null if the manager hasn't yet written the report
    FOREIGN KEY (manager_username) REFERENCES manager(username)
    ON DELETE CASCADE ON UPDATE RESTRICT, #When a manager is deleted his report should also be deleted for the employee. On update restrict -> no username is allowed to change
    FOREIGN KEY (employee_username) REFERENCES employee(username)
    ON DELETE CASCADE ON UPDATE RESTRICT, #When an employee is deleted his report should also be deleted from the table. On update restrict -> no username is allowed to change
	UNIQUE(manager_username, employee_username)
);

DROP TABLE IF EXISTS request_evaluation;
CREATE TABLE request_evaluation(
	empl_username VARCHAR(12) NOT NULL,
    job_id INT(4) NOT NULL,
    PRIMARY KEY(job_id, empl_username),
    FOREIGN KEY (empl_username) REFERENCES employee(username)
    ON DELETE CASCADE ON UPDATE RESTRICT,
    FOREIGN KEY (job_id) REFERENCES job(job_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT #If a job is announced then it should neither be deleted nor be updated.
);

DROP TABLE IF EXISTS evaluation_result;
CREATE TABLE evaluation_result(
	eval_id INT(4) AUTO_INCREMENT NOT NULL,
    empl_username VARCHAR(12) NOT NULL,
    job_id INT(4) NOT NULL,
    grade INT(4) DEFAULT -1,
    comments VARCHAR(255),
    PRIMARY KEY (eval_id),
    FOREIGN KEY (empl_username) REFERENCES employee(username)
    ON DELETE CASCADE ON UPDATE RESTRICT,
    FOREIGN KEY(job_id) REFERENCES job(job_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS eval_phase1;
CREATE TABLE eval_phase1(
	eval_id INT(4) NOT NULL UNIQUE,
    grade_ph1 INT(4) DEFAULT -1,
    id_ph1 INT(4) AUTO_INCREMENT NOT NULL PRIMARY KEY,
    comments VARCHAR(255) DEFAULT "No Comments yet",
    FOREIGN KEY(eval_id) REFERENCES evaluation_result(eval_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS eval_phase2;
CREATE TABLE eval_phase2(
	eval_id INT(4) NOT NULL,
    grade_ph2 INT(4) DEFAULT -1,
    id_ph2 INT(4) AUTO_INCREMENT PRIMARY KEY,
    FOREIGN KEY (eval_id) REFERENCES evaluation_result(eval_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS eval_phase3;
CREATE TABLE eval_phase3(
	eval_id INT(4) NOT NULL,
    grade_ph3 INT(4) DEFAULT -1,
    id_ph3 INT(4) AUTO_INCREMENT PRIMARY KEY,
    FOREIGN KEY (eval_id) REFERENCES evaluation_result(eval_id)
    ON DELETE RESTRICT ON UPDATE RESTRICT
);

DROP TABLE IF EXISTS degree;
CREATE TABLE degree(
	titlos VARCHAR(50) NOT NULL,
    idryma VARCHAR(40) NOT NULL,
    bathmida ENUM('LYKEIO','UNIV','MASTER','PHD') ,
    PRIMARY KEY (titlos, idryma)
);

DROP TABLE IF EXISTS has_degree;
CREATE TABLE has_degree(
	degr_title VARCHAR(50) NOT NULL,
    degr_idryma VARCHAR(40) NOT NULL,
    empl_username VARCHAR(12) NOT NULL,
    etos YEAR(4),
    grade FLOAT(3,1),
    PRIMARY KEY (degr_title, degr_idryma, empl_username),
    FOREIGN KEY (degr_title, degr_idryma) REFERENCES degree(titlos, idryma)
    ON DELETE RESTRICT ON UPDATE RESTRICT,
    FOREIGN KEY (empl_username) REFERENCES employee(username)
    ON DELETE RESTRICT ON UPDATE RESTRICT 
);

DROP TABLE IF EXISTS log;
CREATE TABLE log(
	username VARCHAR(12) NOT NULL,
    date_of_modif DATETIME DEFAULT CURRENT_TIMESTAMP,
    success BOOL NOT NULL,
    on_type ENUM('insert','update','delete') NOT NULL,
    on_table VARCHAR(20) NOT NULL,
    log_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    FOREIGN KEY (username) REFERENCES user(username)
    ON DELETE RESTRICT ON UPDATE CASCADE 
#den mporo na diagrapso xrhsth pou exei kanei allages se pinakes, alla an alla3ei to username tou na ginei cascade oste na mporo
#na bro ton xrhsth pou ekane kapoia allagh (genika gnorizoume oti den epitrepoume allages sto username alla just in case)
);

DROP TABLE IF EXISTS administator;
CREATE TABLE administrator(
	admin_id INT NOT NULL AUTO_INCREMENT,
    admin_username VARCHAR(12) NOT NULL UNIQUE,
    PRIMARY KEY (admin_id),
    FOREIGN KEY (admin_username) REFERENCES user(username)
    ON DELETE RESTRICT ON UPDATE CASCADE
);

DROP TABLE IF EXISTS action;
CREATE TABLE action(
	title VARCHAR(36) PRIMARY KEY,
    descr TINYTEXT NOT NULL
);

DROP TABLE IF EXISTS company_action;
CREATE TABLE company_action(
	firm_afm CHAR(9),
    title VARCHAR(36),
    FOREIGN KEY (title) REFERENCES action(title)
    ON DELETE RESTRICT ON UPDATE CASCADE,
	FOREIGN KEY (firm_afm) REFERENCES company(afm)
    ON DELETE RESTRICT ON UPDATE CASCADE,
    PRIMARY KEY(firm_afm, title)
);



/****************************************************************************************************************************************/
/*************************************************************** INSERT *****************************************************************/
/****************************************************************************************************************************************/

INSERT INTO user(username, password, name, surname, email) VALUES
("Ragnar","Valhalla","Ragnar","Lothbrok","ragnar@gmail.com"), #manager
("Lagertha","shield","Lagertha","Lesbrok","lagertha@gmail.com"), #manager
("Bjorn","RagnarSon","Bjorn","Ironside","bjorn@gmail.com"), #evaluator
("Boneless","killLag","Ivar","Boneless","ivar@yahoo.com"), #evaluator
("Ubbe","123","Ubbe","Ragnarson","ubbe@gmail.com"), #employee
("Hvitserk","areUmad","Hvitserk","Ragnarsson","hvitserk@gmail.com"), #employee
("Rollo","France","Rollo","NotRagnar","rollo@yahoo.com"), #employee
("Vatadim","ceid2021","Vasilis","Milionis","vatadim@hotmail.com"), #admin
("AlexKavou","ceid2021","Alex","Kavoulas","alexKavou@hotmail.com"); #admin

INSERT INTO company(afm, doy, name, phone, street, street_num, city, country) VALUES
("1a345b789", "123doy123", "Coffee-Island", "2103252855", "Leof.Vasileos", "4", "Athens", "Greece");

INSERT INTO administrator(admin_username) VALUES #3exorise admin apo manager!
("Vatadim"),
("AlexKavou");

INSERT INTO manager(username, exp_years, firm_afm) VALUES
("Ragnar", 5, "1a345b789"),
("Lagertha", 3, "1a345b789");

INSERT INTO evaluator(username, exp_years, firm_afm) VALUES
("Bjorn", 7, "1a345b789"),
("Boneless", 4, "1a345b789");

INSERT INTO employee(username, bio, certificates, awards, firm_afm, exp_years) VALUES
("Ubbe","Very obedient","Old Norse - fluent, C2 in English", NULL, "1a345b789", 5),
("Hvitserk","Nah...","Drug Addict",NULL,"1a345b789",3),
("Rollo","King of France","French, English, Old Norse", "Well mannered", "1a345b789", 10);

INSERT INTO project(descr, url) VALUES
("Vitamin additives in coffee", "www.vitacoffee/energyofcoffee/1321.com"),
("Coffee blends and taste", "wwww.typesofcoffee/caffe3213/r3t31.com"),
("ChocoCaramel-Macchiato", "www.choco-caramel/coffee.com"),
("Freddo-Espresso", "www.freddo/espresso.com");

INSERT INTO subject(title, descr, belongs_to) VALUES
("communication_skills", "Should have strong communication skills, inorder to satisfy the customer", NULL),
("barista_skills", "Must know how to use the espresso machine", NULL),
("freddo", "Able to make cold brews", "barista_skills"),
("english", "Be able to take an order in english", "communication_skills"),
("balance", "Have the ability to maintain balance with the trays", NULL);

INSERT INTO has_project(project_id, username_empl) VALUES
(1, "Ubbe"),
(2, "Ubbe"),
(1, "Hvitserk"),
(3, "Hvitserk"),
(3, "Rollo"),
(4, "Rollo");

INSERT INTO languages(empl_username, lang) VALUES
("Ubbe","GR,EN"),
("Hvitserk","GR,EN,SP"),
("Rollo","GR,FR");

INSERT INTO degree(titlos , idryma, bathmida) VALUES
("MHXANIKOS HY" , "CEID", "UNIV"),
("Apolitirio" , "3o Geniko Patras" ,"LYKEIO"),
("Gallikis Filologias" , "EKPA" , "UNIV");

INSERT INTO has_degree(degr_title , degr_idryma, empl_username, etos, grade) VALUES
("Gallikis Filologias" , "EKPA" ,"Rollo", 2000 , 8.2),
("MHXANIKOS HY","CEID","Ubbe", 2010, 6.7);

INSERT INTO job(start_date, salary, position, edra, evaluator_username, announce_date, submission_date) VALUES
("2021-01-01", "1500", "barista", "Athens", "Bjorn", "2020-12-22", "2020-12-29 00:00:00"),
("2021-01-01", "1000", "waiter", "Athens", "Bjorn", "2020-12-22", "2021-11-20 00:00:00"),
("2021-01-01", "2500", "coffee_specialist", "Athens", "Boneless", "2021-12-22", "2020-02-10 00:00:00");

INSERT INTO job_requires(job_id, sub_title) VALUES
(1, "communication_skills"),
(1, "barista_skills"),
(1, "freddo"),
(2, "communication_skills"),
(2, "english"),
(2, "balance");

INSERT INTO request_evaluation(empl_username, job_id) VALUES
("Ubbe",1),
("Ubbe",3),
("Hvitserk",2),
("Rollo",1),
("Rollo",2);

INSERT INTO evaluation_result(empl_username, job_id, grade, comments) VALUES 
("Ubbe", 1, 9, "He aced the interview, very obedient"),
("Ubbe",3,-1,NULL),
("Hvitserk",2,-1,NULL),
("Rollo",1,-1,NULL),
("Rollo",2,-1,NULL);

INSERT INTO eval_phase1(eval_id, grade_ph1, comments) VALUES #max 4
(1, 4, "He aced the interview, very obedient"),
(2,-1,"No Comments yet"),
(3,-1,"No Comments yet"),
(4,-1,"No Comments yet"),
(5,-1,"No Comments yet");

INSERT INTO eval_phase2( eval_id, grade_ph2) VALUES #max 4
(1, 3),
(2,-1),
(3,-1),
(4,-1),
(5,-1);

INSERT INTO eval_phase3( eval_id, grade_ph3) VALUES #max 2
(1, 2),
(2,-1),
(3,-1),
(4,-1),
(5,-1);

INSERT INTO report(manager_username, employee_username, report_text) VALUES
("Ragnar", "Ubbe", "Like Bjorn, but worse");

