/************************************************************* 4.1 trigger ***************************************************************/
#We will be needing 9 triggers in order to update the log table
#We are going to create 2 stored procedures that will be called inside the correct trigger, so we minimize the amount of code being repeated

#Usefull points we used: -> found at: https://dev.mysql.com/doc/refman/8.0/en/trigger-syntax.html
	# A BEFORE trigger is activated by the attempt to insert or modify the row, regardless of whether the attempt subsequently succeeds.
    # An AFTER trigger is executed only if any BEFORE triggers and the row operation execute successfully.
    # For transactional tables, failure of a statement should cause rollback of all changes performed by the statement.
		# Failure of a trigger causes the statement to fail, so trigger failure also causes rollback. 
		# For nontransactional tables, such rollback cannot be done, so although the statement fails, any changes performed prior to the point of the error remain in effect.

SET @usrnm = "admin"; #this should be set after the user login, to be equal to the username of the current user

#stored procedures
DROP PROCEDURE IF EXISTS ins_log;
DELIMITER $
CREATE PROCEDURE ins_log(IN uname VARCHAR(12), IN act ENUM('insert','update','delete'), IN tabl VARCHAR(20))
BEGIN
INSERT INTO log(username, success, on_type, on_table) VALUES
(uname, 0, act, tabl);
END $
DELIMITER ;

DROP PROCEDURE IF EXISTS upd_log;
DELIMITER $
CREATE PROCEDURE upd_log()
BEGIN
	DECLARE id INT;
	SELECT MAX(log_id) INTO id FROM log;
	UPDATE log SET success = 1 WHERE log_id = id;
END $
DELIMITER ;

########################################################################################################################################################################################
######################################################################### JOB ##########################################################################################################
########################################################################################################################################################################################

################################################################### insert triggers ####################################################################################################

DROP TRIGGER IF EXISTS b_trig_ins_job;
DELIMITER $
CREATE TRIGGER b_trig_ins_job
BEFORE INSERT ON job FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'insert', 'job');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_ins_job;
DELIMITER $
CREATE TRIGGER a_trig_ins_job
AFTER INSERT ON job FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -insert- ######################################################################################################


################################################################## update triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_upd_job;
DELIMITER $
CREATE TRIGGER b_trig_upd_job
BEFORE UPDATE ON job FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'update', 'job');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_upd_job;
DELIMITER $
CREATE TRIGGER a_trig_upd_job
AFTER UPDATE ON job FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -update- ######################################################################################################


################################################################## delete triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_del_job;
DELIMITER $
CREATE TRIGGER b_trig_del_job
BEFORE DELETE ON job FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'delete', 'job');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_del_job;
DELIMITER $
CREATE TRIGGER a_trig_del_job
AFTER DELETE ON job FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -delete- ######################################################################################################


########################################################################################################################################################################################
######################################################################### EMPLOYEE #####################################################################################################
########################################################################################################################################################################################

################################################################### insert triggers ####################################################################################################

DROP TRIGGER IF EXISTS b_trig_ins_employee;
DELIMITER $
CREATE TRIGGER b_trig_ins_employee
BEFORE INSERT ON employee FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'insert', 'employee');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_ins_employee;
DELIMITER $
CREATE TRIGGER a_trig_ins_employee
AFTER INSERT ON employee FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -insert- ######################################################################################################


################################################################## update triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_upd_employee;
DELIMITER $
CREATE TRIGGER b_trig_upd_employee
BEFORE UPDATE ON employee FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'update', 'employee');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_upd_employee;
DELIMITER $
CREATE TRIGGER a_trig_upd_employee
AFTER UPDATE ON employee FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -update- ######################################################################################################


################################################################## delete triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_del_employee;
DELIMITER $
CREATE TRIGGER b_trig_del_employee
BEFORE DELETE ON employee FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'delete', 'employee');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_del_employee;
DELIMITER $
CREATE TRIGGER a_trig_del_employee
AFTER DELETE ON employee FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -delete- ######################################################################################################





########################################################################################################################################################################################
################################################################### REQUEST_EVALUATION #################################################################################################
########################################################################################################################################################################################

################################################################### insert triggers ####################################################################################################

DROP TRIGGER IF EXISTS b_trig_ins_request_evaluation;
DELIMITER $
CREATE TRIGGER b_trig_ins_request_evaluation
BEFORE INSERT ON request_evaluation FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'insert', 'request_evaluation');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_ins_request_evaluation;
DELIMITER $
CREATE TRIGGER a_trig_ins_request_evaluation
AFTER INSERT ON request_evaluation FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -insert- ######################################################################################################


################################################################## update triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_upd_request_evaluation;
DELIMITER $
CREATE TRIGGER b_trig_upd_request_evaluation
BEFORE UPDATE ON request_evaluation FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'update', 'request_evaluation');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_upd_request_evaluation;
DELIMITER $
CREATE TRIGGER a_trig_upd_request_evaluation
AFTER UPDATE ON request_evaluation FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -update- ######################################################################################################


################################################################## delete triggers #####################################################################################################

DROP TRIGGER IF EXISTS b_trig_del_request_evaluation;
DELIMITER $
CREATE TRIGGER b_trig_del_request_evaluation
BEFORE DELETE ON request_evaluation FOR EACH ROW
BEGIN
	CALL ins_log(@usrnm, 'delete', 'request_evaluation');
END$
DELIMITER ;

DROP TRIGGER IF EXISTS a_trig_del_request_evaluation;
DELIMITER $
CREATE TRIGGER a_trig_del_request_evaluation
AFTER DELETE ON request_evaluation FOR EACH ROW
BEGIN
	CALL upd_log();
END$
DELIMITER ;

#################################################################### END -delete- ######################################################################################################

/*	#testing
SET @usrnm = "Bjorn";
INSERT INTO job(start_date, salary, position, edra, evaluator_username, submission_date) VALUES
("2021-02-25", "800", "Bartender", "Athens", "Bjorn", "2021-02-22 00:00:00");

SET @temp = 0;
SELECT MAX(job_id) INTO @temp FROM job;

UPDATE job SET position = 'updated' WHERE job_id = @temp;
#WILL DELETE AFTER REQUEST_EVALUATION

INSERT INTO user(username, password, name, surname, email) VALUES
("test_user", "123", "test", "user", "test_user@hotmail.com"); #will be deleted after request_evaluation 
															   #(no trigger will execute, it is just convenient to use a new user for the next modifications)

INSERT INTO employee(username, bio, certificates, awards, firm_afm, exp_years) VALUES
("test_user", "test_test test", "lower", NULL, "1a345b789", 100);
UPDATE employee SET exp_years = 10 WHERE username = "test_user";
#WILL DELETE AFTER REQUEST_EVALUATION

INSERT INTO request_evaluation(empl_username, job_id) VALUES
("test_user", @temp);

CALL deleteApplication("test_user", @temp);
DELETE FROM request_evaluation WHERE empl_username = "test_user";
DELETE FROM employee WHERE username = "test_user";
DELETE FROM user WHERE username = "test_user";
DELETE FROM job WHERE job_id = @temp; */

#exo thn entiposh oti ta error pou mporei na prokipsoun opote na mhn ginei successful to insert/update/delete einai o user pou 8a to kanei
#na mhn einai admin, opote se auth thn periptosh 8a ektelestei to before insert, to insert, to after insert kai meta epeidh 8a doume error
#8a ginei rollback kai 8a afaire8ei h nea eggrafh tou insert kai oles oi energeies pou eginan apo to after insert trigger
#to rollback fainetai apo thn apanthsh sto thread: https://dba.stackexchange.com/questions/233305/mysql-after-insert-trigger-how-to-handle-case-where-no-rows-were-inserted



/************************************************************* 4.2 trigger ***************************************************************/
DROP TRIGGER IF EXISTS forbid_update;
DELIMITER $
CREATE TRIGGER forbid_update
BEFORE UPDATE ON company
FOR EACH ROW
BEGIN
IF NEW.afm != OLD.afm OR NEW.doy != OLD.doy OR NEW.name != OLD.name
THEN 
	SET NEW.afm=OLD.afm;
    SET NEW.doy=OLD.doy;
    SET NEW.name=OLD.name;
END IF;
END $

DELIMITER ;

/*	#testing
UPDATE company SET afm = 'new_afm' WHERE afm = '1a345b789';
UPDATE company SET doy = 'new_doy' WHERE afm = '1a345b789';
UPDATE company SET name = 'new_name' WHERE afm = '1a345b789';*/


/************************************************************* 4.3 trigger ***************************************************************/
# ως στοιχεία προφίλ θεωρώ τα πεδία που βρίσκονται στον πίνακα user
# θεωρώ επίσης ότι κάθε evaluator είναι admin (λόγω της πρότασης "Διαχειριστές του συστήματος (administrator) που υλοποιεί την αξιολόγηση προσωπικού." στη σελίδα 1)
# οι admin μπορούν να μεταβάλλουν password/name/surname/email
# υπάρχει μόνο ένας admin με username admin που δεν είναι evaluator -> just in case


DROP TRIGGER IF EXISTS alter_usr_prof;
DELIMITER $
CREATE TRIGGER alter_usr_prof
BEFORE UPDATE ON user FOR EACH ROW
BEGIN
	DECLARE is_manager INT;
    DECLARE is_employee INT;
    DECLARE is_admin INT;
    
    IF OLD.username != NEW.username THEN 									#απαγορεύεται by default
		SIGNAL SQLSTATE VALUE '45000'
        SET MESSAGE_TEXT = 'you are not allowed to change your username';
	ELSEIF OLD.reg_date != NEW.reg_date THEN 								#απαγορεύεται by default
		SIGNAL SQLSTATE VALUE '45000'
        SET MESSAGE_TEXT = 'you are not allowed to change the date you registered';
    END IF;
    
	SELECT COUNT(*) INTO is_manager FROM manager WHERE username = @usrnm;
	SELECT COUNT(*) INTO is_employee FROM employee WHERE username = @usrnm;
	#SELECT COUNT(*) INTO is_admin FROM administrator WHERE admin_username = @usrnm; #περιττό, αφού ο admin μπορεί να αλλάξει οτιδήποτε δεν απαγορεύεται by default
    
	IF is_manager THEN
		IF OLD.name != NEW.name OR OLD.surname != NEW.surname THEN
			SIGNAL SQLSTATE VALUE '45000'
			SET MESSAGE_TEXT = 'you are not allowed to change neither your name nor surname';
		END IF;
	ELSEIF is_employee THEN
		IF OLD.name != NEW.name OR OLD.surname != NEW.surname OR OLD.email != NEW.email THEN
			SIGNAL SQLSTATE VALUE '45000'
			SET MESSAGE_TEXT = 'you can only change your password';
		END IF;
	END IF;
    
END$
DELIMITER ;


# +-----------+-----------------------------+----------------------+-------------------+
# | Συνοπτικά |	    (επιτρέπεται)  		    |   (δεν επιτρέπεται)  |   (by default)	   |
# + ----------+-----------------------------+----------------------+-------------------+
# | manager   |	     password/email		    |	   name/surname    | username/reg_date |
# | evaluator | password/name/surname/email |	       NULL		   | username/reg_date |
# | employee  |		   password			    |	name/surname/email | username/reg_date |
# +-----------+-----------------------------+----------------------+-------------------+

/*	#testing
SET @usrnm = "admin"; #admin
UPDATE user SET username = 'admin_error' WHERE username = 'admin';
UPDATE user SET reg_date = '2020-01-01 10:10:10+05:30' WHERE username = 'admin';

SET @usrnm = "Ubbe"; #employee
UPDATE user SET name = 'ERROR' WHERE username = 'Ubbe';
UPDATE user SET reg_date = '2020-01-01 10:10:10+05:30' WHERE username = 'Ubbe';

SET @usrnm = "Bjorn"; #evaluator
UPDATE user SET name = 'new_name' WHERE username = 'Bjorn';
UPDATE user SET name = 'Artemis' WHERE username = 'Bjorn';

SET @usrnm = "Ragnar"; #manager
UPDATE user SET surname = 'ERROR' WHERE username = 'Ragnar';*/




/************************************************************ OUR TRIGGERS **************************************************************/

DROP TRIGGER IF EXISTS can_totalgrade1;
DELIMITER $
CREATE TRIGGER can_totalgrade1 #calls a procedure that checks if the other 2 phases have a grade (and if they do updates evaluation_result)
AFTER update ON eval_phase1 FOR EACH ROW
BEGIN
    DECLARE id_thesis INT;
    DECLARE id_eval INT;
    
    SELECT job_id INTO id_thesis FROM evaluation_result WHERE eval_id = NEW.eval_id;
    SELECT evaluator_id INTO id_eval FROM evaluator
    INNER JOIN job ON job.evaluator_username = evaluator.username
    WHERE job_id = id_thesis;
    
    CALL total_grade(id_thesis, id_eval);

END$
DELIMITER ;

##############################################################################################

DROP TRIGGER IF EXISTS can_totalgrade2;
DELIMITER $
CREATE TRIGGER can_totalgrade2 #calls a procedure that checks if the other 2 phases have a grade (and if they do updates evaluation_result)
AFTER update ON eval_phase2 FOR EACH ROW
BEGIN
    DECLARE id_thesis INT;
    DECLARE id_eval INT;
    
    SELECT job_id INTO id_thesis FROM evaluation_result WHERE eval_id = NEW.eval_id;
    SELECT evaluator_id INTO id_eval FROM evaluator
    INNER JOIN job ON job.evaluator_username = evaluator.username
    WHERE job_id = id_thesis;
    
    CALL total_grade(id_thesis, id_eval);

END$
DELIMITER ;

##############################################################################################

DROP TRIGGER IF EXISTS can_totalgrade3;
DELIMITER $
CREATE TRIGGER can_totalgrade3 #calls a procedure that checks if the other 2 phases have a grade (and if they do updates evaluation_result)
AFTER update ON eval_phase3 FOR EACH ROW
BEGIN
    DECLARE id_thesis INT;
    DECLARE id_eval INT;
    
    SELECT job_id INTO id_thesis FROM evaluation_result WHERE eval_id = NEW.eval_id;
    SELECT evaluator_id INTO id_eval FROM evaluator
    INNER JOIN job ON job.evaluator_username = evaluator.username
    WHERE job_id = id_thesis;
    
    CALL total_grade(id_thesis, id_eval);

END$
DELIMITER ;

/*test
INSERT INTO eval_phase2( eval_id, grade_ph2) VALUES
(5,3);
INSERT INTO eval_phase3( eval_id, grade_ph3) VALUES
(5,2);*/

####################################################################################################################

DROP TRIGGER IF EXISTS project_counter; #assings a number at each project of an employee 2h selida 2o bullet
DELIMITER $
CREATE TRIGGER project_counter
BEFORE INSERT ON has_project FOR EACH ROW
BEGIN
	IF (SELECT COUNT(*) FROM has_project WHERE username_empl = NEW.username_empl) = 0 then 
		SET new.empl_proj_num = 1;
	ELSE 
		SET	NEW.empl_proj_num =(SELECT MAX(empl_proj_num) FROM has_project WHERE username_empl=NEW.username_empl)+1;
	END IF;
END $
DELIMITER ;

/*testing
INSERT INTO has_project(project_id, username_empl) VALUES
(3, "tEdMoNTr"),
(4, "tEdMoNTr"),
(5, "tEdMoNTr");*/

#######################################################################################################################

DROP TRIGGER IF EXISTS request_creates_result_id; #if an employee requests for an evaluation, a new record in evaluation_result is being created with grade = NULL
DELIMITER $
CREATE TRIGGER request_creates_result_id
AFTER INSERT ON request_evaluation FOR EACH ROW
BEGIN

	INSERT INTO evaluation_result(empl_username, job_id, grade, comments) VALUES
    (NEW.empl_username, NEW.job_id, -1, NULL);
    
    
    
END $
DELIMITER ;

/*test
INSERT INTO request_evaluation(empl_username, job_id) VALUES
("AxILLEAS",2);*/
DROP TRIGGER IF EXISTS creates_insert_phases;
DELIMITER $
CREATE TRIGGER creates_insert_phases
AFTER INSERT ON evaluation_result FOR EACH ROW
BEGIN 
	INSERT INTO eval_phase1(eval_id, comments) VALUES
    (NEW.eval_id, "No Comments yet");
    INSERT INTO eval_phase2(eval_id) VALUES
    (NEW.eval_id);
    INSERT INTO eval_phase3(eval_id) VALUES
    (NEW.eval_id);
    
END$
DELIMITER ;
/*testing
INSERT INTO request_evaluation(empl_username, job_id) VALUES ("aLcONzoI","3");*/

#######################################################################################################################

DROP TRIGGER IF EXISTS announce_curDate;
DELIMITER $
CREATE TRIGGER announce_curDate
BEFORE INSERT ON job
FOR EACH ROW
BEGIN
SET NEW.announce_date=now();
END$
DELIMITER ;
/*testing
INSERT INTO job(start_date, salary, position, edra, evaluator_username, submission_date)
VALUES ("2021-02-15","10","b","a","aRTOncom","2021-02-28");*/


DROP TRIGGER IF EXISTS checkPhase1;
DELIMITER $
CREATE TRIGGER checkPhase1
BEFORE UPDATE ON eval_phase1
FOR EACH ROW
BEGIN
	IF (NEW.grade_ph1 < -1 OR NEW.grade_ph1 > 4) then
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'GRADE PHASE1 MUST BE BETWEEN 0 AND 4 '; 
	END IF;
END$
DELIMITER ;
/*testing
update eval_phase1 set grade_ph1="5" where eval_id="1"; */

#############################################################################################
DROP TRIGGER IF EXISTS checkPhase2;
DELIMITER $
CREATE TRIGGER checkPhase2
BEFORE UPDATE ON eval_phase2
FOR EACH ROW
BEGIN
	IF (NEW.grade_ph2 < -1 OR NEW.grade_ph2 > 4) then
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'GRADE PHASE2 MUST BE BETWEEN 0 AND 4 '; 
	END IF;
END $
delimiter ;
################################################################################################

DROP TRIGGER IF EXISTS checkPhase3;
DELIMITER $
CREATE TRIGGER checkPhase3
BEFORE UPDATE ON eval_phase3
FOR EACH ROW
BEGIN
	IF (NEW.grade_ph3 < -1 OR NEW.grade_ph3 > 2) then
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'GRADE PHASE3 MUST BE BETWEEN 0 AND 2 '; 
	END IF;
END $
DELIMITER ;

DROP TRIGGER IF EXISTS isSubmissionDue;
DELIMITER $
CREATE TRIGGER isSubmissionDue BEFORE INSERT ON request_evaluation
FOR EACH ROW
BEGIN
	DECLARE subm_date DATE;
	SELECT job.submission_date INTO subm_date FROM job WHERE job.job_id = NEW.job_id;
	IF subm_date < current_date() THEN
		SIGNAL SQLSTATE VALUE '45000'
		SET MESSAGE_TEXT = 'Cannot apply for a job whose submission date is due!';
	END IF;
END $
DELIMITER ;

/*testing
CALL finalizeJobUpdate("aLcONzoI",4);
CALL deleteApplication("aLcONzoI",4);*/

