# ccnx-ldplib v0.9.0

##  Functional System Design (FSD)

This document is released under the terms of the [Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0)

Copyright 2014 IoTone, Inc.


Author/Owner:        David J. Kordsmeier

Version/Date:        v0.9.0



**Abstract:**

Developers need secure, easy way to discover or advertise (publish) devices and services in a manner that can work without prior knowledge of network addresses, and can span across networks.  CCNx offers a secure protocol that can be used to support easy discovery of devices and services.  This solution enables each client device or service to publish metadata periodically, in order to "register" under a particular namespace.  Once registered, the API offers ways to discover peers, and enumerate details of peers.  The CCNx Lightweight Discovery Protocol Lib is the API impelentation written in C language.  By utilizing name heirarchies rather than relying upon the ephemeral nature of network addressing, the CCNx LDP library enables local and global scenarios for service and and device discovery.



**Last Modified: 8/23/2014 17:30:00    **

# CONTACT & DISTRIBUTION

**Prepared by:** David J. Kordsmeier (dkords@iotone.io)

**Contributors:**

**Primary Contact:**

N/A

# REVISION HISTORY

Revision history is available on github: https://github.com/IoTone/ccnx-ldplib/commits/master/docs/ccnx-ldplib-fsd.md

*1.0* __QUALITY CONTROL__

  *1.1* __Development Methodology__

For the purposes of this project we are using a combination of XP and traditional waterfall model.

  *1.2* __Change Control__

All code will be managed by git source control. Changes to this specification will be reflected in this document and reviewed by the team. Spec Reviewers should "sign off" in the "Revision History" section (via Git commits or Gibhub Issues).
 
  *1.3* __Audit Plan__

QA testing will be performed by a continuous integration server before finalizing release.

*2.0* __PROJECT MANAGEMENT FRAMEWORK__

This section list some general definitions and constrains around the project described in the FSD.
 
  *2.1* __System Overview__

In a typical deployment scenario, devices are operating in proximity to each other by a variety of network interfaces: Bluetooth, WiFi, 4G, or some network interface to be defined.  Devices may enter and leave networks, and networks may change status between available and unavailable.

Services are deployed with the notion they should be available to devices or other services.  For devices or services to communicate, they will typically need to find each other on the network.

  *2.2* __Definitions__

Describe the scope of work

  - CCNx LDP Client : Any device or service using the CCNx Lightweight Discovery Protocol.

  - CCNx LDP Peer : Any network connected CCNx LDP Client.

  - CCNx LDP Command Protocol : The protocol for allowing CCNx LDP Peers to send commands to each other. 

  - CCNx LDP Metadata :  The metadata contains key, unique identifying attributes of a CCNx LDP Client, as well as any other attributes required by clients. 

  - CCNx LDP Service: A service is defined as a capability provided to a Peer 

  - CCNx LDP Local Discovery Service : The service that handles discovery of CCNx LDP Client Peers running on a local network, allowing connections to be established with zero configuration or some user input.

  - CCNx LDP Remote Client : Remote designation indicates the CCNx LDP Client is operating on a remote network or operating on a different subnet 

  - CCNx LDP Discovery Phase : The phase in which CCNx LDP Clients register their metadata and optionally finds CCNx LDP Peer to interact with  

  - CCNx LDP Errors : All Errors that occur in the course of using CCNx LDP.  The errors are defined contain enough information to diagnose issues. 

  - CCNx LDP Namespace : Any URI that identifies the namespace used for discovery and registration.  Applications and Services should agree upon useful namespaces

  *2.3* __Assumptions__

The following assumptions are made regarding this project:

- All CCNx LDP clients are running their own ccnd gateway, and are on the same API version
- Handling losses of connectivity and managing errors in the network transport are the responsibility
- No distinction is made between the kinds of devices, they could be mobiles, servers, or IoT nodes.
- It is assumed that Assymetric Keys are acceptable for use by CCNx LDP Clients
 
  *2.4* __Risks and Pitfalls__

- The biggest risk is in managing the complexity in briding connectivity across subnets and in a WAN

  *2.5* __Key Performance Indicators (KPIs)__

The KPIs for ccnx-ldplib are concerned with the latency and scalability:

- 100ms to receive a response on a discovery request for local subnet
- 100ms to write 10K of data during a registration request
- 100ms to enumerate 1000 5K nodes in a particular namespace

  *2.6* __Test Harness and Benchmark Design__

Latency benchmark

Pre-Conditions:

- 2 Peers on same subnet
- low amount of traffic on the subnet

Inputs:

- Peer A metadata
- Peer B metadata

Outputs:

- start time discovery request
- stop time discovery request complete

Post-Conditions:

- Peer A has received all metadata
- Peer A has recorded discovery request latency


Metadata Registration benchmark

Pre-Conditions:

- 2 Peers on same subnet
- low amount of traffic on the subnet

Inputs:

- Peer A metadata
- Peer B metadata

Outputs:

- start time metadata write request by Peer A
- stop time metadata write request complete by Peer A
- start time metadata discovery request by Peer B
- stop time metadata discovery request complete by Peer B

Post-Conditions:

- Peer A has received all metadata
- Peer A has recorded discovery request latency

1K Name Enumeration Benchmark

Pre-Conditions:

- 1 Peers on same subnet
- low amount of traffic on the subnet

Inputs:

- Peer A metadata
- Peer B1-B1000 metadata

Outputs:

- start time discovery request
- stop time discovery request complete

Post-Conditions:

- Peer A has received all metadata
- Peer A has recorded discovery request latency

  *2.7* __Roles and Responsibilities__

Development and QA will be performed by the IoTone team.


*3.0* __FUNCTIONAL SYSTEM DESIGN__

  *3.1* __Feature Specification__

| **Feature** | **Description** | **ID** |
| --- | --- | --- |
| Peer Metadata Format | The Metadata is used by Clients to publish their information and find Peers | 3.1.1 |
| CMD Message Format | When CCNx LDP Commands are sent, there is a Request/Response format that will be used | 3.1.2 |
| Content Naming Scheme  | Data exchanged between Peers will be organized under hierarchical naming schemes for CCNx LDP | 3.1.3 |
| Registration Phase | Each Peer must register to publish metadata | 3.1.4 |
| Discovery Phase | Remote CCNx LDP Client has to discover Peers | 3.1.5 |
| Error Messages | Errors are defined for all possible error conditions | 3.1.6 |
| | |

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

- [Apple Bonjour](https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/NetServices/Introduction.html#//apple_ref/doc/uid/TP40002445-SW1): While addressing the same feature set as CCNx LDP, it does not address a number of key points.  There is no mention of security in the Bonjour protocol.  For example, one has no way to verify the authenticity of a service or host.  Malicious devices can easily get involved in MITM attacks and spoof a valid host or service.  There is no notion of access control. Any host can access any published service.  And due to the implementation, without special provisions at the router level, Bonjour is not designed to operate across subnets, limiting its usefulness for 'global' scale deployments.  There are a number of descriptions for how to use [DNS-sd](http://dns-sd.org), multicast-routing, or proxy-bonjour services.
- [UPnP](): UPnP is another strong standard that offers a lot in terms of scope.  The working group behind UPnP contains the majority of network gear heavyweights. What it does not address is security.  In fact, security holes have [attracted the attention of the US-CERT organization](http://www.zdnet.com/how-to-fix-the-upnp-security-holes-7000010584/).

