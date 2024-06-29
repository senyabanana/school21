#!/bin/bash

scp /home/gitlab-runner/builds/Ar3z6Y_U/0/students/DO6_CICD.ID_356283/claudinm_student.21_school.ru/DO6_CICD-1/src/cat/s21_cat claudinm@10.0.2.4:/usr/local/bin/
scp /home/gitlab-runner/builds/Ar3z6Y_U/0/students/DO6_CICD.ID_356283/claudinm_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep claudinm@10.0.2.4:/usr/local/bin/
ssh claudinm@10.0.2.4 ls -lah /usr/local/bin