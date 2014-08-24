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

**Distribution:**

Free distribution under 

# REVISION HISTORY

Add link to this document's commit history.

1.0 QUALITY CONTROL
  1.1. Development Methodology

For the purposes of this project we are using a combination of XP and traditional waterfall model.

  1.2 Change Control

All code will be managed by source control. Changes to the specification will be reflected in this document and reviewed by the team. Reviewers should "sign off" in the "Revision History" section.
 
  1.3 Audit Plan

QA testing will be performed by a continuous integration server before finalizing release.

2.0 PROJECT MANAGEMENT FRAMEWORK

This section list some general definitions and constrains around the project described in the FSD.

 
  2.1. System Overview

Describe the system here

  2.2 Scope

Describe the scope of work

  2.3 Assumptions

The following assumptions are made regarding this project:

- TODO
 
  2.3 Risks and Pitfalls

- TODO

  2.4 Key Performance Indicators (KPIs)

Define KPIs

  2.5 Test Harness and Benchmark Design

TODO

Pre-Conditions:

- list pre conditions

Inputs:

- list inputs

Outputs:

- list outputs

Post-Conditions:

- list post conditions


  2.6 Roles and Responsibilities

Todo

3.0 FUNCTIONAL SYSTEM DESIGN
  3.1 Feature Specification

| **Feature** | **Description** | **ID** |
| --- | --- | --- |
| stuff | things | foo |

  3.1 Infrastructure

There is no support infrastructure required in this project.
 
  3.2 Platform

The following devices are planned for local testing to validate the design:

- Samsung Galaxy S2
- Nexus 7 (gen 2)
- Dell x86 Android 8"
- Linux x86 Server

  3.3 Operating Systems

Android 4.0.x – 4.4.x must be supported.

  3.4 Languages and Input Methods

N/A

  3.5 Network

The network will not be used in the app and should be turned off for testing.

  3.6 Development Tools

Development tools used:

- --Android sdk

  3.7 Operational Support

N/A

  3.8 Process Design

Add a diagram

  3.9 UI Specification

N/A

  3.10 Data Model

N/A

4.0 Software Quality

All software delivered for this project will undergo a Software Quality Engineering Testing Phase at each milestones deliverable. The goal of testing is to ensure delivery of code that meets required quality standards for this project at each phase.

To ensure quality, we will run a standard Agile approach to testing, known as Continuous Testing. At each checkin/code commit, a complete set of unit tests will are run, in addition to system test deployment, and manual testing.

For each phase, all software delivered will be delivered with all P1 and P2 bugs fixed. P3 bugs will be analyzed during bug triage meetings and deferred on a case by case basis with input from the team. Bug Severity is described below:

- P1 – System Critical or Show stopper, prevents system function
- P2 – Major Bug, affects major feature or functionality, but does not prevent system from functioning
- P3 – Minor Bug, affects functionality, but does not adversely impact the system or user experience
- P4 – Low Priority, generally addresses cosmetic issues but has little effect on functionality. Usually used to ensure bug will be deferred until after release.
- P5 – Insignificant or Informative issue, typically a note to developer to decide how to prioritize issue, as RFE or as Not-A-Bug. 

Bugs will be tracked in Github Issues for this project.  Anyone will be able to add bugs or make comments.  The development team is willing to take constructive pull requests without a contributor agreement.

  4.1 Test Plan

| **Summary** | **Description** | **Expected Result** | **ID** |
| --- | --- | --- | --- |
| a summary | a descr. | expected | 1.1.1 |


  4.2 Test Case Design

TODO

5.0 APPENDIX A - WORK PLAN AND DELIVERABLES SCHEDULE

N/A - No need to do this.  It will all get done this week

6.0 APPENDIX B - References

N/A - No need to do this.  It will all get done this week

