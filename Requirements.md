
# Requirements for Hospital Project 




## Functional Requirements:

1. The system should provide a user interface for the hospital staff to use.

2. The data of the patients should be saved in a log file.

3. The system should allow adding patients who have come to the ER on their own.

4. The system should allow adding patients who came to the ER through an ambulance.

5. The system should prioritize patients based on whether they arrived by ambulance or not.

6. The system should assign a seat number to patients who arrived on their own

7. The system should remove a patient from the list when they have received successful treatment.

8. The system should allow querying which seat partners a patient has.

9. The system should only return seat partners if the patient has been assigned a seat.

## Non-functional Requirements:

1. The system should be user-friendly and easy to use.

2. The system should be reliable and accurate.

3. The system should be fast and responsive.

4. The system should be secure and protect patients information

5. The system should be scalable and able to handle a large number of patients.

## Constraints:

    The project should be fully completed by 13th June

    The program should be implemented nad programmed in English language.

    The programing will be implemented with C language

## User stories

1. As a hospital staff member, I want to be able to add patients who arrived at the ER on their own, so that they can be prioritized and assigned a seat if possible.

2. As a hospital staff member, I want to be able to add patients who arrived at the ER through an ambulance, so that they can be prioritized for urgent treatment.

3. As a hospital staff member, I want to be able to remove a patient from the system after they have received successful treatment, so that they are no longer listed and can make room for new patients.

4. As a hospital staff member, I want to be able to query which seat partners a patient has, so that in case of an infectious disease outbreak, the hospital can notify the seat partners of the affected patient.

5. As a hospital staff member, in case where all seats are occupied, I want to assign patients to a standing list / queue so that when a free seat is available they can be assigned to it.

 

## Acceptance Stories

1)

**Given**: A patient arrives at the ER on their own

**When**: A hospital staff member adds their information to the system

**Then**: The patient should be prioritized and assigned a seat if possible.

2)

**Given**: Patient arrives at the ER through an ambulance

**When**: A hospital staff member adds their information to the system

**Then**: The patient should be prioritized for urgent treatment.

 

3)

**Given**: A patient has received successful treatment

**When**: A hospital staff member removes their information from the system

**Then**: The patient should be removed from the list.

 

4)

**Given**: At least 1 patient is removed from the list

**When**: Next patient treatment is decided

**Then**: Hospital staff checks if there is a new ambulance arrival – If not the next patient on the list will be chosen.




### Authors: 
Mohanad. A, Philipp. H, Favour. R, Dominik. B
