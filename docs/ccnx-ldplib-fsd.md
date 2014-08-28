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

Devices and Services must first know how to introspect their own metadata, or the Application calling the CCNx LDP API must be responsible for writing out well formed metadata.  By publishing metadata, a device in effect, advertises its availability on a network under a particular namespace.  By using namespaces, a device has the possibility of assigning its membership to a particular federation group of Peers, independent of the network address.

  *2.2* __Definitions__

  - CCNx LDP Client : Any device or service using the CCNx Lightweight Discovery Protocol.

  - CCNx LDP Namespace : Any URI that identifies the namespace used for discovery and registration.  Applications and Services should agree upon useful namespaces

  - CCNx LDP Peer : Any network connected CCNx LDP Client.

  - CCNx LDP Peer Group : Any CCNx LDP Peers registered under a particular namespace.

  - CCNx LDP Peer Keystore : Every Peer should provide a keystore in order to ensure all requests can be verified.  A keystore is unnecessary if verification is off.

  - CCNx LDP Command Protocol : The protocol for allowing CCNx LDP Peers to send commands to each other. 

  - CCNx LDP Metadata :  The metadata contains key, unique identifying attributes of a CCNx LDP Client, as well as any other attributes required by clients. 

  - CCNx LDP Service: A service is defined as a capability provided to a Peer 

  - CCNx LDP Local Discovery Service : The service that handles discovery of CCNx LDP Client Peers running on a local network, allowing connections to be established with zero configuration or some user input.

  - CCNx LDP Remote Client : Remote designation indicates the CCNx LDP Client is operating on a remote network or operating on a different subnet 

  - CCNx LDP Registration Phase : The phase in which CCNx LDP Clients registers its metadata in order to join a particular peer group namespace

  - CCNx LDP Discovery Phase : The phase in which CCNx LDP Clients finds CCNx LDP Peer to interact with  

  - CCNx LDP Errors : All Errors that occur in the course of using CCNx LDP.  The errors are defined contain enough information to diagnose issues. 

  - ~~CCNx LDP CMD Message: The way in which messages are passed back and forth between Peers is by writing to the Peer’s namespace using a CMD Message~~

  - ~~CCNx LDP Correlation ID : Used in CMD Messages to uniquely identify related messages~~

  - ~~CCNx LDP Locator URI : Used in CMD Messages to offer an alternative way to address the remote peer id~~

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
| ~~CMD Message Format~~ | ~~When CCNx LDP Commands are sent, there is a Request/Response format that will be used~~ | ~~3.1.2~~ |
| Access Control for Namespaces| Namespaces can be  | 3.1.2 |
| Content Naming Scheme  | Data exchanged between Peers will be organized under hierarchical naming schemes for CCNx LDP | 3.1.3 |
| Registration Phase | Each Peer must register to publish metadata | 3.1.4 |
| Discovery Phase | Remote CCNx LDP Client has to discover Peers | 3.1.5 |
| Error Messages | Errors are defined for all possible error conditions | 3.1.6 |
| | |

Note, 3.1.2 CMD Message has been stricken from the feature set, as there is no need to support CMD Messages in the spec.  It will be replaces with an access control feature.

  *3.1.1* __Peer Metadata Format__

* The Peer Metadata is intended to be an internal representation of Peer state at any given time.  A structured format is preferred over a list or config file.  To simplify the effort, Peer Metadata is based on the [Universal Device Metadata Specification]() and/or the Universal Service Metadata, and offers a superset of attributes.  Each required attribute is described as follows: 

* peer-id: a name defined by a Peer to uniquely identify this peer as a member of a Peer Group.  TODO: Define how we deal with duplicate peer-ids, and spoofing of peer-ids.  Also explain how peer-ids are generated. 

* usm_services: An array containing the services exported by this Peer.  A usm_services object is defined in the Universal Service Metadata Spefication.

* udm_devices: An array containing the devices exported by this Peer.  A usm_devices object is defined in the Universal Device Metadata Spefication.

* status: Represents the state of the Peer [available, pairing, paired, unpairing, unavailable] 

* status-detail:  Will contain additional detail for the status, or null if there is no additional detail. 

```
{
   "peer-id":"1230sdf1290000012",
   "usm_services":[
      {
         "usm_key":"froglegs.local",
         "usm_type":"webserver"
      }
   ],
   "udm_devices":[
      {
         "udm_key":"0585b8a6",
         "udm_model_name":"Nexus",
         "udm_model_number":"Nexus 7",
         "udm_oem":"ASUS",
         "udm_guid":"0585b8a6",
         "udm_os_version":"4.4.2",
         "udm_os":"Android",
         "udm_type":"tablet",
         "udm_memory_volatile":{
            "size":"1GB"
         },
         "udm_memory_non_volatile":{
            "size":"16GB",
            "type":"flash"
         },
         "udm_chipset_details":{
            "udm_chipset_inst_set":"armeabi-v7a",
            "udm_chipset_vendor":"Qualcomm",
            "udm_chipset_type":"Snapdragon S4Pro",
            "udm_cpu_max_frequency":"1.5 GHz",
            "udm_cpu_number_of_cores":"4"
         },
         "udm_displays":[
            {
               "display_resolution":"1200x1824",
               "ppi":"323"
            }
         ],
         "udm_network_interfaces":[
            {
               "lo":[
                  {
                     "address":"127.0.0.1",
                     "family":"IPv4",
                     "internal":true
                  },
                  {
                     "address":"::1",
                     "family":"IPv6",
                     "internal":true
                  }
               ]
            },
            {
               "wlan0":[
                  {
                     "address":"10.0.0.105",
                     "family":"IPv4",
                     "internal":false
                  },
                  {
                     "address":"fe80::de85:deff:fe90:4cb9",
                     "family":"IPv6",
                     "internal":false
                  }
               ]
            }
         ],
         "udm_sensors":{
            "accelerometer":"1",
            "light":"1",
            "gyroscope":"1",
            "orientation":"1",
            "magnetic":"1",
            "sound":"1"
         }
      }
   ],
   "status":"available",
   "status-detail":null
}
```

  *3.1.2* __Access Control for Namespaces~~CMD Message Format~~__

It is important to implement access control for namespaces.  For certain deployments or applications, the administrator will choose to implement access control groups on namespaces and on particular content.  Due to the complexity of the solution, it is up to each implementation of a CCNx LDP Discovery Service to provide access control.

In reality, the implementation of the solution relies upon a CCNd running, which will honor Access Control Markers within a Content Object.  Therefore, the scope of implementation of Access Control Groups falls outside this specification.  It is noted here simply to inform the implementer that the APIs must report Access Control errors.  The first implementation of this specification will require handling Access Control configuration in a manner that is to be determined.  Peer Keys must be utilized in the configuration process, which is also not part of tihs specification.  For further details, review the section on Access Control Groups in the Appendix B.

  *3.1.3* __Content Naming Scheme__

In order to implement this design independent of the network hardware location, or transport, we will use a technique based around naming, where all participants in the network are named, all content is named, and all participants are verifiable based on the name and associated keys used to sign content. 

We will organize the following hierarchy of naming: 

-    DEFAULT_LDP_NAMESPACE “ccnx:/ldp.iotone.io” 

-    DEFAULT_LDP_PEERGROUP “ccnx:/ldp.iotone.io/pg/default” 

-    DEFAULT_LDP_PEERGROUP_PEERS “ccnx:/ldp.iotone.io/pg/default/peers” 

-    DEFAULT_LDP_PEERGROUP_PEERS_PEERID_PREFIX  “ccnx:/ldp.iotone.io/pg/default/peers/%s” 

-    DEFAULT_LDP_PEERGROUP_PEERS_PEERID_SYNC_TOPO_PREFIX  “ccnx:/ldp.iotone.io/pg/default/peers/%s/sync-info” 

-    DEFAULT_LDP_PEERGROUP_PEERS_PEERID_METADATA_1.0.0  “ccnx:/ldp.iotone.io/pg/default/peers/%s/metadata_1.0.0” 

-    ~~DEFAULT_LDP_PEERGROUP_PEERS_PEERID_CMD_PREFIX  “ccnx:/ldp.iotone.io/pg/default/peers/%s/CMD”~~

If we substitute the %s for a peer-id, we can start to see how data gets organized.  Every member of a Peer Group will have the above information defined in their Local Discovery Service. 

  *3.1.4* __Registration Phase__

Diagram A below describes the process in which an LDP Client can register itself as an LDP Peer to a particular Peer Group.  Each LDP Client will be running or have available a Local Discovery Service, which is where the Clients register themselves as Peers.  

*DIAGRAM A*<sup>1</sup>
```
        start registration
        +-----------+                                      
        |           |       Publish Peer                   
        |           |       Metadata {                     
        |    +------v-----+   peer-id:       +------------+
+-------+    | Local      |    ....          | Joined     |
|Peer A |    | Discovery  | }                | Peer       |
+-------+    | Service    +-+----------------> Group      |
             |            | +----------------+            |
             +------------+ |                +------------+
                            |                              
+-------+----+------------+------------------+------------+
+-------+    +------------+ |                +------------+
|Peer B |    | Local      <-+ Route interests|            |
+-------+    | Discovery  |   in metadata to |            |
             | Service    |   adjacent peers |            |
             |            |                  |            |
             +------------+                  +-------- ---+

```
1: Diagram source: http://asciiflow.com/#0B2j69b0ryZjAelVmdGd0dFBlU0k

Once registered, a client is free to initiate a discovery request, in which they will receive Peer Metadata (Defined in Section 3.1.1).  It is up to a Remote Client to discern whether or not to accept communications from a particular Peer.  This case below describes a situation where there are only two Peers.



  *3.1.5* __Discovery Phase__

*Diagram B*<sup>2</sup>
```
         Start Discovery                                   
        +-----------+                                      
        |           |       Get PeerPeer                   
        |           |       Metadata {                     
        |    +------v-----+   peer-id:       +-------+----+
+-------+    | Local      |    ....          | Retreive   |
|Peer A |    | Discovery  | }                | Peer       |
+-------+    | Service    <-+----------------+ Group      |
             |            | +----------------> Metadata   |
             +------------+ |                +------------+
                            |                              
+-------+----+------------+------------------+------------+
+-------+    +------------+ |                +------------+
|Peer B |    | Local      +-+ Route interests| Previously |
+-------+    | Discovery  |   in metadata to | Joined in  |
             | Service    |   adjacent peers | Peer       |
             |            <------------------+ Group      |
             +------------^                  +------------+
```
2: Diagram source: http://asciiflow.com/#0B2j69b0ryZjAbS1yZ0Zhc0x4dE0

  *3.1.6* __Error Messages__

The following error message format is defined below.  If an attribute called ldp_error is defined in a response message ~~CMD response message~~, it will contain the following object value:

```
{
  "ldp_errno": "Error number",
  "ldp_msg": "Error message",
  "ldp_rootcause": "Error root cause"
}
```

The errno is defined with known error codes:

-  0  : No error, status ok
- -1  : General error
- -10 : Cannot reach local naming services
- -11 : Malformed Request
- -12 : Malformed Response
- -13 : Unauthorized Access to namespace
- -14 : Invalid credentials
- -15 : Cryptographic error
- -16 : Broken Pipe
- -17 : Network Unreachable
- -100 : Unknown error

  *3.2* __Infrastructure__

There is no support infrastructure required in this project.
 
  *3.3* __Platform__

The following devices are planned for local testing to validate the design:

- Samsung Galaxy S2
- Nexus 7 (gen 2)
- Dell x86 Android 8"
- Linux x86 Server

  *3.4* __Operating Systems__

Android 4.0.x – 4.4.x must be supported.  Linux x86, ARM.  Mac OS X.   Windows.

  *3.5* __Languages and Input Methods__

N/A

  *3.6* __Network__

Assumption for testing is that devices will be using TCP/IP over Wifi, ethernet, or possibly a 4G network.  For purposes of testing, the project will focus on TCP/IP and WiFi.

  *3.7* __Development Tools__

Development tools used:

- gcc
- make
- Android SDK

  *3.8* __Operational Support__

N/A

  *3.9* __Process Design__

See detailed diagrams defined in __3.1.1 - 3.1.6__.

  *3.10* __UI Specification__

N/A

  *3.11* __Data Model__

The datamodel is fully defined in 3.1.1 and 3.1.2.

  *3.12* __API__

```
typedef struct LDPSettings TLDPSettings;
TLDPSettings *ldp_settings_create(void);
void ldp_settings_destroy(TLDPSettings **settings);
int ldp_settings_init(TLDPSettings *settings);
int ldp_settings_set_sys_fs_path(TLDPSettings *settings, char *path);
int ldp_settings_set_sys_logfile(TLDPSettings *settings, char *path);
int ldp_settings_set_user_id(TLDPSettings *settings, char *user_id);
int ldp_settings_set_keystore_uri(TLDPSettings *settings, char *keystore_uri);
int ldp_write_peer_metadata_from_bytes(char *peer_id_common_name, char *metadata, char *access_control_obj, TLDPServiceHandle *handle);
char * ldp_get_peer_metadata_as_bytes(char *remote_peer_id_common_name, size_t *data_length, char *access_control_obj, TLDPServiceHandle *handle);
char ** ldp_get_peers(int *peer_names_length, char *access_control_obj, TLDPServiceHandle *handle);
```

*4.0* __Software Quality__

All software delivered for this project will undergo a Software Quality Engineering Testing Phase at each milestones deliverable. The goal of testing is to ensure delivery of code that meets required quality standards for this project at each phase.

To ensure quality, we will run a standard Agile approach to testing, known as Continuous Testing. At each checkin/code commit, a complete set of unit tests will are run, in addition to system test deployment, and manual testing.

For each phase, all software delivered will be delivered with all P1 and P2 bugs fixed. P3 bugs will be analyzed during bug triage meetings and deferred on a case by case basis with input from the team. Bug Severity is described below:

- P1 – System Critical or Show stopper, prevents system function
- P2 – Major Bug, affects major feature or functionality, but does not prevent system from functioning
- P3 – Minor Bug, affects functionality, but does not adversely impact the system or user experience
- P4 – Low Priority, generally addresses cosmetic issues but has little effect on functionality. Usually used to ensure bug will be deferred until after release.
- P5 – Insignificant or Informative issue, typically a note to developer to decide how to prioritize issue, as RFE or as Not-A-Bug. 

Bugs will be tracked in [Github Issues for this project](https://github.com/IoTone/ccnx-ldplib/issues).  Anyone will be able to add bugs or make comments.  The development team is willing to take constructive pull requests without a contributor agreement.

  *4.1* __Test Plan__

| **Summary** | **Description** | **Expected Result** | **ID** |
| --- | --- | --- | --- |
| Validate Peer Metadata | Peer Metadata should be valid | Conforms to definition in 3.1.1 | TC4.1.1 |
| ~~Parse CMD Format~~ | ~~All messages going in and out should be valid and parseable into component form, as described in 3.1.2~~ | ~~Conforms to definition in 3.1.2~~ | ~~TC4.1.2~~ |
| Verify naming schema | All content should be defined using a common naming scheme, defined in 3.1.3 | Conforms to definition in 3.1.3 | TC4.1.3 |
| Perform Registration Request | A client should be able to perform registration as defined in 3.1.4 | Conforms to definition in 3.1.4 | TC4.1.4 |
| Perform a Discovery Request | A client should be able to perform discovery as defined in 3.1.5 | Conforms to definition in 3.1.5 | TC4.1.5 |
| Errors are defined and thrown at right times | A client should get proper error reporting when error conditions occur | Conforms to definition in 3.1.6 | TC4.1.6 |


  *4.2* __Test Case Design__

Test cases will be designed using Google Test 1.6.0 (https://code.google.com/p/googletest/).  Google Test is C++ based, though it can be used to test the C code base.

Units will verify api conformance and correctness.

System tests can be run to verify the functioning of the system.  Simulating two network peers will require either a remote trigger or a manual process execution.  For purposes of this project, manual testing will be used to validate system functionality.  Results will be published under the testresults directory.

*5.0* __Implementation__

  *5.1* __Dependencies__

- CCNx 0.8.0 API & Implementation
- jsmn: http://zserge.bitbucket.org/jsmn.html
- bstrlib (TBD)

  *5.2* __Software__

The API will exist as standalone headers, with a hidden private interface.  The code will exist as a portable library which can be included into 3rd party projects.

*6.0* __APPENDIX A - WORK PLAN AND DELIVERABLES SCHEDULE__

N/A - No need to do this.  It will all get done this week

*7.0* __APPENDIX B - References__

- [Apple Bonjour](https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/NetServices/Introduction.html#//apple_ref/doc/uid/TP40002445-SW1): While addressing the same feature set as CCNx LDP, it does not address a number of key points.  There is no mention of security in the Bonjour protocol.  For example, one has no way to verify the authenticity of a service or host.  Malicious devices can easily get involved in MITM attacks and spoof a valid host or service.  There is no notion of access control. Any host can access any published service.  And due to the implementation, without special provisions at the router level, Bonjour is not designed to operate across subnets, limiting its usefulness for 'global' scale deployments.  There are a number of descriptions for how to use [DNS-sd](http://dns-sd.org), multicast-routing, or proxy-bonjour services.
- [UPnP](http://upnp.org/specs/arch/UPnP-arch-DeviceArchitecture-v1.0.pdf): UPnP is another strong standard that offers a lot in terms of scope.  The working group behind UPnP contains the majority of network gear heavyweights. What it does not address is security.  In fact, security holes have [attracted the attention of the US-CERT organization](http://www.zdnet.com/how-to-fix-the-upnp-security-holes-7000010584/).
- [CCNx Access Control Specification 2010](https://github.com/RazortoothRTC/ccnx/blob/26-forward-port-v0.7.2-release-to-0.8.0/doc/specs/AccessControl/AccessControlSpecs01.pdf?raw=true) : The specification explains how access control groups work and are to be implemented.