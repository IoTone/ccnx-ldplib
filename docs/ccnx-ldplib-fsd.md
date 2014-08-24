# ccnx-ldplib v0.9.0

##  Functional System Design (FSD)

This document is released under the terms of the [Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0)

Copyright 2014 IoTone, Inc.


Author/Owner:        David J. Kordsmeier

Version/Date:        v0.9.0



**Abstract:**

Developers need secure, easy way to discover devices and services in a manner that can work without prior knowledge of network addresses, and can span across networks.  CCNx offers a secure protocol that can be used to support easy discovery of devices and services.  The abridged description of this solution involves each client device or service to publish metadata periodically, in order to "register" under a particular namespace.  Once registered, the API offers ways to discover peers, and enumerate details of peers.



**Last Modified: 8/23/2014 17:30:00    **

# CONTACT & DISTRIBUTION

**Prepared by:** David J. Kordsmeier (dkords@iotone.io)

**Contributors:**

**Primary Contact:**

N/A

# REVISION HISTORY

Add link to this document's commit history.

*1.0* __QUALITY CONTROL__

  *1.1* __Development Methodology__

For the purposes of this project we are using a combination of XP and traditional waterfall model.

  *1.2* __Change Control__

All code will be managed by git source control. Changes to this specification will be reflected in this document and reviewed by the team. Spec Reviewers should "sign off" in the "Revision History" section.
 
  *1.3* __Audit Plan__

QA testing will be performed by a continuous integration server before finalizing release.

*2.0* __PROJECT MANAGEMENT FRAMEWORK__

This section list some general definitions and constrains around the project described in the FSD.
 
  *2.1* __System Overview__

Describe the system here

  *2.2* __Scope__

Describe the scope of work

  *2.3* __Assumptions__

The following assumptions are made regarding this project:

- TODO
 
  *2.4* __Risks and Pitfalls__

- TODO

  *2.5* __Key Performance Indicators (KPIs)__

Define KPIs

  *2.6* __Test Harness and Benchmark Design__

TODO

Pre-Conditions:

- list pre conditions

Inputs:

- list inputs

Outputs:

- list outputs

Post-Conditions:

- list post conditions


  *2.7* __Roles and Responsibilities__

Todo

*3.0* __FUNCTIONAL SYSTEM DESIGN__

  *3.1* __Feature Specification__

| **Feature** | **Description** | **ID** |
| --- | --- | --- |
| stuff | things | foo |

  *3.2* __Infrastructure__

There is no support infrastructure required in this project.
 
  *3.3* __Platform__

The following devices are planned for local testing to validate the design:

- Samsung Galaxy S2
- Nexus 7 (gen 2)
- Dell x86 Android 8"
- Linux x86 Server

  *3.4* __Operating Systems__

Android 4.0.x – 4.4.x must be supported.

  *3.5* __Languages and Input Methods__

N/A

  *3.6* __Network__

The network will not be used in the app and should be turned off for testing.

  *3.7* __Development Tools__

Development tools used:

- --Android sdk

  *3.8* __Operational Support__

N/A

  *3.9* __Process Design__

Add a diagram

  *3.10* __UI Specification__

N/A

  *3.11* __Data Model__

N/A

*4.0* __Software Quality__

All software delivered for this project will undergo a Software Quality Engineering Testing Phase at each milestones deliverable. The goal of testing is to ensure delivery of code that meets required quality standards for this project at each phase.

To ensure quality, we will run a standard Agile approach to testing, known as Continuous Testing. At each checkin/code commit, a complete set of unit tests will are run, in addition to system test deployment, and manual testing.

For each phase, all software delivered will be delivered with all P1 and P2 bugs fixed. P3 bugs will be analyzed during bug triage meetings and deferred on a case by case basis with input from the team. Bug Severity is described below:

- P1 – System Critical or Show stopper, prevents system function
- P2 – Major Bug, affects major feature or functionality, but does not prevent system from functioning
- P3 – Minor Bug, affects functionality, but does not adversely impact the system or user experience
- P4 – Low Priority, generally addresses cosmetic issues but has little effect on functionality. Usually used to ensure bug will be deferred until after release.
- P5 – Insignificant or Informative issue, typically a note to developer to decide how to prioritize issue, as RFE or as Not-A-Bug. 

Bugs will be tracked in Github Issues for this project.  Anyone will be able to add bugs or make comments.  The development team is willing to take constructive pull requests without a contributor agreement.

  *4.1* __Test Plan__

| **Summary** | **Description** | **Expected Result** | **ID** |
| --- | --- | --- | --- |
| a summary | a descr. | expected | 1.1.1 |

  *4.2* __Test Case Design__

TODO

*5.0* __APPENDIX A - WORK PLAN AND DELIVERABLES SCHEDULE__

N/A - No need to do this.  It will all get done this week

*6.0* __APPENDIX B - References__

N/A - No need to do this.  It will all get done this week

