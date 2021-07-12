/***************************************************************** 3.1 STORED PROCEDURE ********************************************/

DROP PROCEDURE IF EXISTS get_all_application;
DELIMITER $
CREATE PROCEDURE get_all_application(IN name VARCHAR(25), IN surname VARCHAR(35))
proc_label:BEGIN
	DECLARE usr VARCHAR(12);
    DECLARE id INT;
    DECLARE pos VARCHAR(40);
    DECLARE sal FLOAT(6,1);
    DECLARE evname VARCHAR(25);
    DECLARE evsur VARCHAR(35);
    DECLARE ph1 INT;
    DECLARE ph2 INT;
    DECLARE ph3 INT;
    DECLARE total INT;
    DECLARE myflag INT DEFAULT 0;
    
    DECLARE curs CURSOR FOR
	SELECT job.job_id, job.position, job.salary, user.name, user.surname, evaluation_result.grade, eval_phase1.grade_ph1, eval_phase2.grade_ph2, eval_phase3.grade_ph3
    FROM request_evaluation
    LEFT JOIN job ON job.job_id = request_evaluation.job_id
    RIGHT JOIN user ON user.username = job.evaluator_username
    INNER JOIN evaluation_result ON evaluation_result.job_id = job.job_id AND evaluation_result.empl_username = usr
    INNER JOIN eval_phase1 ON eval_phase1.eval_id = evaluation_result.eval_id
    INNER JOIN eval_phase2 ON eval_phase2.eval_id = evaluation_result.eval_id
    INNER JOIN eval_phase3 ON eval_phase3.eval_id = evaluation_result.eval_id
    WHERE request_evaluation.empl_username = usr;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET myflag = 1; 
    
    SELECT user.username INTO usr
    FROM user 
    WHERE user.name = name AND user.surname = surname;
    IF usr IS NULL THEN
		SELECT "That is not a valid user";
		LEAVE proc_label;
	END IF;
    
    OPEN curs;
    FETCH curs INTO id, pos, sal, evname, evsur, ph1, ph2, ph3, total;
    WHILE myflag = 0 DO
		IF total = -1 THEN
			SELECT "IN PROGRESS" AS STATUS, id, pos, sal, evname, evsur, ph1, ph2, ph3;
		ELSE
			SELECT "COMPLETED" AS STATUS, id, pos, sal, evname, evsur, total;
        END IF;
		FETCH curs INTO id, pos, sal, evname, evsur, ph1, ph2, ph3, total;
	END WHILE;
    CLOSE curs;
    
END $
DELIMITER ;

#CALL get_all_application("Ubbe","Ragnarson");
#CALL get_all_application("Achileas","Adamou");

/***************************************************************** 3.2 STORED PROCEDURE ********************************************/

DROP PROCEDURE IF EXISTS total_grade;
DELIMITER $
CREATE PROCEDURE total_grade(IN jid INT, IN evalid INT)
BEGIN
	DECLARE evid INT;
	DECLARE comnts TEXT;
    DECLARE grade1, grade2, grade3 INT;
    
	DECLARE myflag INT DEFAULT 0;
    DECLARE curs CURSOR FOR
    SELECT eval_id FROM evaluation_result WHERE job_id = jid AND grade = "-1";
#if grade != null and one of the 3 grades has been changed (which is not allowed) then
#the total grade will update aswell -> NOT ALLOWED

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET myflag = 1;
    
    #check if evid and jid do match
    IF (SELECT COUNT(*) FROM job WHERE job_id = jid AND evaluator_username IN 
			(SELECT username FROM evaluator WHERE evaluator_id = evalid)) = 0 THEN
		SIGNAL SQLSTATE VALUE '45000'
        SET MESSAGE_TEXT = 'job_id and eval_id do not match';
    END IF;
    
    OPEN curs;
    FETCH curs INTO evid;
    
    WHILE myflag = 0 DO
		SELECT grade_ph1 INTO grade1
        FROM eval_phase1 WHERE eval_id = evid;
		SELECT comments INTO comnts
        FROM eval_phase1 WHERE eval_id = evid;
		SELECT grade_ph2 INTO grade2
        FROM eval_phase2 WHERE eval_id = evid;
		SELECT grade_ph3 INTO grade3
        FROM eval_phase3 WHERE eval_id = evid;
        IF grade1 != -1 AND grade2 != -1 AND grade3 != -1 THEN
            UPDATE evaluation_result SET evaluation_result.comments = comnts, grade = grade1 + grade2 + grade3 WHERE eval_id = evid;
        END IF;
        FETCH curs INTO evid;
    END WHILE;
    CLOSE curs;

END $
DELIMITER ;

#CALL total_grade(3,2); #expect error
#CALL total_grade(15,3); #expect error
#CALL total_grade(3,3); #expect to work

/***************************************************************** 3.3 STORED PROCEDURE ********************************************/

DROP procedure IF EXISTS evaluation_status;
USE staff_evaluation;
DELIMITER $
CREATE PROCEDURE evaluation_status(IN counter INT)

BEGIN

IF(SELECT count(*) from evaluation_result where grade != -1 and job_id=counter )=0
THEN 
	SELECT "COMPLETED";
	SELECT *
    FROM evaluation_result 
    WHERE job_id=counter AND grade != -1 ORDER BY empl_username DESC;
	
ELSE 
	 SELECT * FROM evaluation_result WHERE grade != -1 AND job_id=counter ORDER BY empl_username DESC ;
    
     select "IN PROGRESS", count(empl_username) from evaluation_result where grade = -1 AND job_id = counter;
END IF;

END $
DELIMITER ;

#CALL evaluation_status(1);

/**************************************************** OTHER **********************************************************************/

DROP PROCEDURE IF EXISTS verify_user;
DELIMITER $
CREATE PROCEDURE verify_user(IN uname VARCHAR(12), IN pass VARCHAR(10))
BEGIN
	DECLARE onoma VARCHAR(12);
    DECLARE kodikos VARCHAR(10);
      
     
    IF (SELECT COUNT(*) FROM user WHERE BINARY user.username = uname) = 0 THEN
		SELECT "-1";
	ELSEIF (SELECT COUNT(*) FROM user WHERE BINARY user.username = uname AND user.password = pass) = 0 THEN
		SELECT "0";
	ELSEIF (SELECT COUNT(*) FROM user WHERE BINARY user.username = uname AND user.password = pass) = 1 THEN
		IF (SELECT COUNT(*) FROM administrator WHERE BINARY admin_username = uname) = 1 THEN
			SELECT "1";
		ELSEIF (SELECT COUNT(*) FROM evaluator WHERE BINARY evaluator.username = uname) = 1 THEN
			SELECT "2";
		ELSEIF (SELECT COUNT(*) FROM manager WHERE BINARY username = uname) = 1 THEN
			SELECT "3";
		ELSEIF (SELECT COUNT(*) FROM employee WHERE BINARY employee.username = uname) = 1 THEN
			SELECT "4";
		ELSE
			SIGNAL SQLSTATE '45000'
			SET MESSAGE_TEXT = "Fatal Error Occurred while trying to IDENTIFY the user!";
		END IF;
    ELSE
		SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = "Fatal Error Occurred while trying to VERIFY the user!";
    END IF;
END $
DELIMITER ;

/*testing
CALL verify_user("bad", "pass"); #out -1
CALL verify_user("admin", "admin"); #out 0
CALL verify_user("admin", "admin123"); #out 1
CALL verify_user("aRTOncom", "-7FeRz"); #out 2
CALL verify_user("aTeRaLit", "#E+c3J"); #out 3
CALL verify_user("aLcONzoI", "c8F#T8"); #out 4*/




/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/********************************************************** EVALUATOR ****************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

DROP PROCEDURE IF EXISTS getEvalProf;
DELIMITER $
CREATE PROCEDURE getEvalProf(IN usernm VARCHAR(12))
BEGIN
	SELECT u.name, u.surname, u.password , evaluator.exp_years, evaluator.evaluator_id, evaluator.firm_afm ,u.email
	FROM user AS u
	INNER JOIN evaluator ON u.username=evaluator.username
    where u.username=usernm;
END $
DELIMITER ;

/*testing
call getEvalProf("aRTOncom");*/


DROP PROCEDURE IF EXISTS show4JobFields;
DELIMITER $
CREATE PROCEDURE show4JobFields(IN username varchar(25),  job_id int)
BEGIN 
DECLARE x varchar(25);
DECLARE y INT;
#SELECT evaluator.username INTO x FROM evaluator WHERE evaluator.username=username;
#SELECT job.job_id INTO y FROM job WHERE job.job_id=job_id;
SELECT job.salary,job.announce_date,job.start_date,job.submission_date, job.job_id FROM evaluator 
INNER JOIN job ON job.evaluator_username=evaluator.username
WHERE evaluator.username=username AND job.job_id=job_id;
end $
DELIMITER ;

/*testing
CALL show4JobFields("CHoEInGt", "2");*/


DROP PROCEDURE IF EXISTS showAllCompanyResults;
DELIMITER $
CREATE PROCEDURE showAllCompanyResults(IN username VARCHAR(25))
BEGIN
DECLARE x CHAR(9) ;
SELECT evaluator.firm_afm INTO x FROM evaluator WHERE evaluator.username=username;
SELECT evaluation_result.empl_username,evaluation_result.grade,eval_phase1.comments,eval_phase1.grade_ph1,eval_phase2.grade_ph2,eval_phase3.grade_ph3 
FROM evaluator 
right JOIN job ON job.evaluator_username=evaluator.username
right JOIN company ON company.afm=evaluator.firm_afm
RIGHT JOIN evaluation_result on job.job_id=evaluation_result.job_id
right join eval_phase1 on eval_phase1.eval_id=evaluation_result.eval_id
right join eval_phase2 on eval_phase2.eval_id=evaluation_result.eval_id
right join eval_phase3 on eval_phase3.eval_id=evaluation_result.eval_id
WHERE company.afm=x AND evaluation_result.grade != -1;
end $
DELIMITER ;

/*testing
CALL showAllCompanyResults("Bjorn");*/


DROP PROCEDURE IF EXISTS showCompanysJobs;
DELIMITER $
CREATE PROCEDURE showCompanysJobs(IN username Char(9))
BEGIN 

SELECT evaluator.username, evaluator.firm_afm, job.job_id, job.position, job.salary, job.start_date, job.submission_date 
FROM evaluator 
INNER JOIN job ON job.evaluator_username=evaluator.username
INNER JOIN company ON company.afm=evaluator.firm_afm
WHERE company.afm=evaluator.firm_afm AND evaluator.username = username;
end $
DELIMITER ;

/*testing
CALL showCompanysJobs("aRTOncom");*/


DROP PROCEDURE IF EXISTS showMyJobs;
DELIMITER $
CREATE PROCEDURE showMyJobs(IN username varchar(25))
BEGIN 
DECLARE x varchar(25);
SELECT evaluator.username INTO x FROM evaluator WHERE evaluator.username=username;
SELECT job.job_id,job.position,job.salary,job.announce_date,job.start_date,job.submission_date FROM evaluator 
INNER JOIN job ON job.evaluator_username=evaluator.username
WHERE evaluator.username=x;
end $
DELIMITER ;

/*testing
CALL showMyJobs("aRTOncom");*/


DROP PROCEDURE IF EXISTS show5ResultFields;
DELIMITER $
CREATE PROCEDURE show5ResultFields(IN username VARCHAR(25), job_id INT, empl VARCHAR(25))
BEGIN 
DECLARE x varchar(25);
DECLARE  y INT ;
DECLARE z VARCHAR(25);
SELECT evaluation_result.empl_username,evaluation_result.grade,eval_phase1.comments,eval_phase1.grade_ph1,eval_phase2.grade_ph2,eval_phase3.grade_ph3 
FROM evaluator 
right JOIN job ON job.evaluator_username=evaluator.username
right JOIN company ON company.afm=evaluator.firm_afm
RIGHT JOIN evaluation_result on job.job_id=evaluation_result.job_id
right join eval_phase1 on eval_phase1.eval_id=evaluation_result.eval_id
right join eval_phase2 on eval_phase2.eval_id=evaluation_result.eval_id
right join eval_phase3 on eval_phase3.eval_id=evaluation_result.eval_id
WHERE evaluator.username=username AND job.job_id=job_id AND evaluation_result.empl_username=empl;
UPDATE eval_phase1 SET eval_phase1.grade_ph1="1" WHERE evaluation_result.evaluator_username=username and job.job_id=job_id and evaluation_result.empl_username=empl;

end $
DELIMITER ;

/*testing
CALL show5ResultFields("CHoEInGt", "2","AtEOnoLz");
CALL show5ResultFields("aRTOncom", "1","aLcONzoI");*/


DROP PROCEDURE IF EXISTS showMyResults;
DELIMITER $
CREATE PROCEDURE showMyResults(IN username VARCHAR(25))
BEGIN 
DECLARE x varchar(25);
SELECT evaluator.username INTO x FROM evaluator WHERE evaluator.username=username;
SELECT job.job_id,job.position,evaluation_result.empl_username,evaluation_result.grade,eval_phase1.comments,eval_phase1.grade_ph1,eval_phase2.grade_ph2,eval_phase3.grade_ph3 
FROM evaluator 
right JOIN job ON job.evaluator_username=evaluator.username
right JOIN company ON company.afm=evaluator.firm_afm
RIGHT JOIN evaluation_result on job.job_id=evaluation_result.job_id
right join eval_phase1 on eval_phase1.eval_id=evaluation_result.eval_id
right join eval_phase2 on eval_phase2.eval_id=evaluation_result.eval_id
right join eval_phase3 on eval_phase3.eval_id=evaluation_result.eval_id
WHERE evaluator.username=x;
end $
DELIMITER ;

/*testing
CALL showMyResults("aRTOncom");*/


DROP PROCEDURE IF EXISTS updatePhases;
DELIMITER $
CREATE PROCEDURE updatePhases(IN empl varchar(12), IN jobID int , IN  ph1 int , IN ph2 int, IN ph3 int , IN comms Varchar(255))
BEGIN 
	DECLARE id INT;
	DECLARE gr INT;
    DECLARE subdate DATE;
    
	SELECT grade INTO gr FROM evaluation_result WHERE empl_username=empl AND job_id=jobID;    
	SELECT eval_id INTO id FROM evaluation_result WHERE empl_username = empl AND job_id = jobID ;
	SELECT eval_id INTO id FROM evaluation_result WHERE empl_username = empl AND job_id = jobID;
    SELECT submission_date INTO subdate FROM job WHERE job_id = jobID;
    IF (subdate > curdate()) THEN
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'Cannot update application, since submission date is not due';
	END IF;
    IF gr != -1 THEN 
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'Not allowed to change grades/comments when result is finalized';
    END IF;
    UPDATE eval_phase1 set comments=comms WHERE eval_id = id;
	UPDATE eval_phase1 SET grade_ph1=ph1 WHERE eval_id = id;
    UPDATE eval_phase2 SET grade_ph2=ph2 WHERE eval_id = id;
    UPDATE eval_phase3 SET grade_ph3=ph3 WHERE eval_id = id;
    END$
    DELIMITER ;

/*testing
CALL updatePhases("aLcONzoI","5","2","2","1","sss");*/





/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/********************************************************** MANAGER ******************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

DROP PROCEDURE IF EXISTS changeSalary;
DELIMITER $
CREATE PROCEDURE changeSalary(IN afm char(9))
BEGIN
	SELECT job.job_id, job.position, job.salary
    FROM job
    LEFT JOIN evaluator ON evaluator.username = job.evaluator_username
    LEFT JOIN company ON company.afm = evaluator.firm_afm
    WHERE company.afm = afm;
END $
DELIMITER ;	

/*testing
CALL changeSalary("c8765d321");*/


DROP PROCEDURE IF EXISTS evaluationEmplRes;
DELIMITER $
CREATE PROCEDURE evaluationEmplRes(IN afm CHAR(9))
BEGIN
	SELECT job.position, job.salary, name, surname, evaluation_result.grade, job.submission_date
    FROM evaluator
    RIGHT JOIN job ON job.evaluator_username = evaluator.username
    RIGHT JOIN evaluation_result ON evaluation_result.job_id = job.job_id
    LEFT JOIN user ON user.username = evaluation_result.empl_username
    WHERE job.submission_date < CURDATE() AND evaluator.firm_afm = afm AND evaluation_result.grade != -1
    GROUP BY job.job_id
    HAVING MAX(evaluation_result.grade)
    ORDER BY job.position, evaluation_result.grade;
    
END $
DELIMITER ;

/*testing
CALL evaluationEmplRes("1a345b789");
CALL evaluationEmplRes("c8765d321");*/


#Apparently mySQL does not have a full outer join option, so I need to implement it using unions of left and right joins
#https://stackoverflow.com/questions/4796872/how-to-do-a-full-outer-join-in-mysql

DROP PROCEDURE IF EXISTS evaluatorAverage;
DELIMITER $
CREATE PROCEDURE evaluatorAverage(IN afm CHAR(9))
BEGIN
	SELECT evaluator.username, user.name, user.surname, AVG(evaluation_result.grade)
    FROM evaluator
    INNER JOIN user ON user.username = evaluator.username
    RIGHT JOIN job ON job.evaluator_username = evaluator.username
	RIGHT JOIN evaluation_result ON evaluation_result.job_id = job.job_id
    WHERE evaluator.firm_afm = afm AND evaluation_result.grade != -1
    GROUP BY evaluator.username
    UNION
	SELECT evaluator.username, user.name, user.surname, AVG(evaluation_result.grade)
    FROM evaluator
    INNER JOIN user ON user.username = evaluator.username
    LEFT JOIN job ON job.evaluator_username = evaluator.username
	RIGHT JOIN evaluation_result ON evaluation_result.job_id = job.job_id
    WHERE evaluator.firm_afm = afm AND evaluation_result.grade != -1
    GROUP BY evaluator.username
    UNION
	SELECT evaluator.username, user.name, user.surname, AVG(evaluation_result.grade)
    FROM evaluator
    INNER JOIN user ON user.username = evaluator.username
    RIGHT JOIN job ON job.evaluator_username = evaluator.username
	LEFT JOIN evaluation_result ON evaluation_result.job_id = job.job_id
    WHERE evaluator.firm_afm = afm AND evaluation_result.grade != -1
    GROUP BY evaluator.username
    UNION
	SELECT evaluator.username, user.name, user.surname, AVG(evaluation_result.grade)
    FROM evaluator
    INNER JOIN user ON user.username = evaluator.username
    LEFT JOIN job ON job.evaluator_username = evaluator.username
	LEFT JOIN evaluation_result ON evaluation_result.job_id = job.job_id
    WHERE evaluator.firm_afm = afm AND evaluation_result.grade != -1
    GROUP BY evaluator.username;
END $
DELIMITER ;

/*testing
CALL evaluatorAverage("1a345b789");*/


DROP PROCEDURE IF EXISTS get_all_applications;
DELIMITER $
CREATE PROCEDURE get_all_applications(IN name VARCHAR(25), IN surname VARCHAR(35))
proc_label:BEGIN
	DECLARE usr VARCHAR(12);
    SELECT user.username INTO usr
    FROM user 
    WHERE user.name = name AND user.surname = surname;
    IF usr IS NULL THEN
		SELECT "That is not a valid user";
		LEAVE proc_label;
	END IF;

	SELECT job.job_id, job.position, job.salary, user.name, user.surname, evaluation_result.grade, eval_phase1.grade_ph1, eval_phase2.grade_ph2, eval_phase3.grade_ph3
    FROM request_evaluation
    LEFT JOIN job ON job.job_id = request_evaluation.job_id
    RIGHT JOIN user ON user.username = job.evaluator_username
    INNER JOIN evaluation_result ON evaluation_result.job_id = job.job_id AND evaluation_result.empl_username = usr
    INNER JOIN eval_phase1 ON eval_phase1.eval_id = evaluation_result.eval_id
    INNER JOIN eval_phase2 ON eval_phase2.eval_id = evaluation_result.eval_id
    INNER JOIN eval_phase3 ON eval_phase3.eval_id = evaluation_result.eval_id
    WHERE request_evaluation.empl_username = usr;
    
END$
DELIMITER ;

/*testing
CALL get_all_applications("Ubbe","Ragnarsson");
CALL get_all_applications("Achileas","Adamou");
CALL get_all_applications("Alkinoos","Ioannidis");*/


DROP PROCEDURE IF EXISTS getComp;
DELIMITER $
CREATE PROCEDURE getComp(IN usr VARCHAR(12))
BEGIN
	SELECT c.name, c.afm, c.doy, c.phone, c.country, c.city, c.street, c.street_num
               FROM company AS c
               RIGHT JOIN manager AS m ON m.firm_afm = c.afm
               WHERE m.username = usr;
END $
DELIMITER ;

/*testing
CALL getComp("manager");*/


DROP PROCEDURE IF EXISTS getEmployees_ofManager;
DELIMITER $
CREATE PROCEDURE getEmployees_ofManager(IN usr VARCHAR(12) )
BEGIN
	DECLARE etaireia char(9);
    SELECT firm_afm INTO etaireia FROM manager WHERE username = usr;
    
    SELECT u.surname, u.name
    FROM user AS u
    RIGHT JOIN employee ON employee.username = u.username
    WHERE employee.firm_afm = etaireia
    ORDER BY u.surname ASC;
END $
DELIMITER ;

/*testing
CALL getEmployees_ofManager("manager");*/


DROP PROCEDURE IF EXISTS getProf;
DELIMITER $
CREATE PROCEDURE getProf(IN usr VARCHAR(12))
BEGIN
	SELECT u.name, u.surname, u.password, u.email
	FROM user AS u
	WHERE u.username = usr;
END $
DELIMITER ;

/*testing
CALL getProf("manager");*/


DROP PROCEDURE IF EXISTS getReports;
DELIMITER $
CREATE PROCEDURE getReports(IN emp VARCHAR(12))
BEGIN
	SELECT report.manager_username, report.report_text
    FROM report
    WHERE report.employee_username = emp;
END $
DELIMITER ;

/*testing
CALL getReports("aLcONzoI");*/






/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/********************************************************** EMPLOYEE *****************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

DROP PROCEDURE IF EXISTS applicationsToDelete;
DELIMITER $
CREATE PROCEDURE applicationsToDelete(IN username VARCHAR(12))
BEGIN

SELECT re.job_id, job.position, job.submission_date, evaluation_result.grade, evaluation_result.comments 
FROM request_evaluation AS re
INNER JOIN employee ON employee.username= re.empl_username
INNER JOIN job ON re.job_id=job.job_id
RIGHT JOIN evaluation_result ON re.job_id=evaluation_result.job_id AND re.empl_username=evaluation_result.empl_username
WHERE employee.username=username;

END$
DELIMITER ;

/*testing
CALL applicationsToDelete("aLcONzoI");*/


DROP PROCEDURE IF EXISTS degree_update;
DELIMITER $
CREATE PROCEDURE degree_update(IN username VARCHAR(12), IN GUItitlos VARCHAR(50), IN GUIgrade FLOAT(3,1), IN institution VARCHAR(40), IN GUIbathmida ENUM('LYKEIO','UNIV','MASTER','PHD'), IN etos_ktisis YEAR)
BEGIN
	IF (SELECT COUNT(*) FROM degree WHERE titlos = GUItitlos AND idryma = institution) = 0 THEN
		INSERT INTO degree(titlos , idryma, bathmida) VALUES
		(GUItitlos , institution, GUIbathmida);
	END IF;
    
    IF (SELECT COUNT(*) FROM has_degree WHERE empl_username = username AND degr_title = GUItitlos AND degr_idryma = institution) = 0 THEN
		INSERT INTO has_degree(degr_title, degr_idryma, empl_username, etos, grade) VALUES
		(GUItitlos, institution, username, etos_ktisis, GUIgrade);
	END IF;
		    
END $
DELIMITER ;

/*testing
CALL degree_update("aLcONzoI", "SpecialDegree", "10", "CEID", "UNIV", 2014);
CALL degree_update("aLcONzoI", "MHXANIKOS HY_PM", "10", "CEID PATRAS", "MASTER", 2016);*/


DROP PROCEDURE IF EXISTS deleteApplication; #we could just use ON DELETE CASCADE (when we initially created the tables)
DELIMITER $
CREATE PROCEDURE deleteApplication(IN username VARCHAR(12), IN jobID INT)
BEGIN
	DECLARE id INT;
    DECLARE subdate DATE;
	SELECT eval_id INTO id FROM evaluation_result WHERE empl_username = username AND job_id = jobID;
    SELECT submission_date INTO subdate FROM job WHERE job_id = jobID;
    IF (subdate <= curdate()) THEN
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'Cannot delete application, since submission date is due';
	END IF;
	DELETE FROM eval_phase1 WHERE eval_id = id;
    DELETE FROM eval_phase2 WHERE eval_id = id;
    DELETE FROM eval_phase3 WHERE eval_id = id;
    DELETE FROM evaluation_result WHERE eval_id = id;
    DELETE FROM request_evaluation WHERE empl_username = username AND job_id = jobID;
END $
DELIMITER ;

/*testing
CALL deleteApplication("aLcONzoI","4");*/


DROP PROCEDURE IF EXISTS finalizeJobUpdate;
DELIMITER $
CREATE PROCEDURE finalizeJobUpdate(IN username VARCHAR(12), IN jobID INT)
BEGIN
	DECLARE id INT;
	INSERT INTO request_evaluation(empl_username, job_id) VALUES
	(username,jobID);
    SELECT eval_id INTO id FROM evaluation_result WHERE empl_username = username AND job_id = jobID;
END $
DELIMITER ;

/*testing
CALL finalizeJobUpdate("aLcONzoI","4");*/


#last updated 12/02/21
DROP PROCEDURE IF EXISTS get_applications;
DELIMITER $
CREATE PROCEDURE get_applications(IN username VARCHAR(12))
BEGIN

SELECT re.job_id, job.position, evaluation_result.grade, evaluation_result.comments 
FROM request_evaluation AS re
INNER JOIN employee ON employee.username= re.empl_username
INNER JOIN job ON re.job_id=job.job_id
RIGHT JOIN evaluation_result ON re.job_id=evaluation_result.job_id AND re.empl_username=evaluation_result.empl_username
WHERE employee.username=username;

END$
DELIMITER ;

/*testing
CALL get_applications("aLcONzoI");*/


DROP PROCEDURE IF EXISTS getDegrees;
DELIMITER $
CREATE PROCEDURE getDegrees(IN username VARCHAR(12))
BEGIN
	SELECT degree.bathmida, degree.titlos, hd.grade, degree.idryma, hd.etos
    FROM has_degree AS hd
    INNER JOIN degree ON degree.titlos = hd.degr_title AND degree.idryma = hd.degr_idryma
    WHERE hd.empl_username = username;
END $
DELIMITER ;

/*testing
CALL getDegrees("lagiMAtE");*/


DROP PROCEDURE IF EXISTS getEmplProf;
DELIMITER $
CREATE PROCEDURE getEmplProf(IN usernm VARCHAR(12))
BEGIN
	SELECT u.name, u.surname, u.password ,employee.bio
	FROM user AS u
	INNER JOIN employee ON u.username=employee.username
    where u.username=usernm;
END $
DELIMITER ;

/*testing
CALL getEmplProf("aLcONzoI");*/


#created for updateApplications (employee) 11.02.2021
DROP PROCEDURE IF EXISTS getJobInfo;
DELIMITER $
CREATE PROCEDURE getJobInfo(IN jobID INT)
BEGIN
	SELECT job.salary, job.edra, job.submission_date
    FROM job
    WHERE job.job_id = jobID;
END$
DELIMITER ;

/*testing
CALL getJobInfo("1");*/


DROP PROCEDURE IF EXISTS getJobrequirements;
DELIMITER $
CREATE PROCEDURE getJobrequirements(IN jobID INT)
BEGIN
	SELECT subject.title, subject.belongs_to, subject.descr
    FROM job_requires
    INNER JOIN subject ON subject.title = job_requires.sub_title
    WHERE job_requires.job_id = jobID;
END $
DELIMITER ;

/*testing
CALL getJobrequirements("4");*/


DROP PROCEDURE IF EXISTS getProjects;
DELIMITER $
CREATE PROCEDURE getProjects(IN username VARCHAR(12))
BEGIN
	SELECT hp.empl_proj_num, project.descr, project.url
    FROM has_project AS hp
    INNER JOIN project ON project.project_id = hp.project_id
    WHERE hp.username_empl = username;
END $
DELIMITER ;

/*testing
CALL getProjects("aLcONzoI");*/


DROP PROCEDURE IF EXISTS project_update;
DELIMITER $
CREATE PROCEDURE project_update(IN username VARCHAR(12), IN pid TINYINT, IN descript TEXT, IN u VARCHAR(60) )
BEGIN
	DECLARE max_num INT;
    DECLARE proID INT;
    SELECT MAX(empl_proj_num) INTO max_num
    FROM has_project
    WHERE username_empl = username;
	IF pid > max_num OR max_num IS NULL THEN
		IF (SELECT COUNT(*) FROM project WHERE url = u) = 0 THEN
			INSERT INTO project(descr, url) VALUES
			(descript, u);
		END IF;
        SELECT project_id INTO proID FROM project WHERE url = u;
        INSERT INTO has_project(project_id, username_empl) VALUES
		(proID, username);
	ELSE
		SELECT COUNT(*), max_num FROM project WHERE url = u;
		SELECT project_id INTO proID FROM has_project WHERE empl_proj_num = pid AND username_empl = username;
        UPDATE project SET descr = descript, url = u WHERE project_id = proID;
	END IF;		
END $
DELIMITER ;

/*testing
CALL project_update("aLcONzoI", "0", "lol it WORKS!", "NEWurl.com");
CALL project_update("aLcONzoI", "3", "Project for spotify's datas", "www.spotify/dataaa/wfr123.com");
CALL project_update("aLcONzoI", "4", "Totaly new project created int project_update!", "this_is_a_unique_url.com");*/


#updated 11/2/2021
DROP PROCEDURE IF EXISTS updateApplications;
DELIMITER $
CREATE PROCEDURE updateApplications(IN username VARCHAR(25))
BEGIN
	SELECT job.job_id, job.position
    FROM job
    INNER JOIN evaluator ON evaluator.username = job.evaluator_username
    INNER JOIN employee ON employee.firm_afm = evaluator.firm_afm
    WHERE employee.username = username AND
    job_id NOT IN( SELECT job_id FROM request_evaluation WHERE empl_username = username );
END$
DELIMITER ;

/*testing
CALL updateApplications("aLcONzoI");*/


