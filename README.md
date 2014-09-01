Overview
========

CCNx Lightweight Discovery Protocol Lib (ccnx-ldplib).  

Author
======

David J. Kordsmeier
IoTone, Inc.
github: truedat101
twitter: @dkords
irc: truedat101

Problem
=======

Developers need secure, easy way to discover devices and services in a manner that can work without prior knowledge of network addresses, and can span across networks.

Solution
========

CCNx offers a secure protocol that can be used to support easy discovery of devices and services.  The abridged description of this solution involves each client device or service to publish metadata periodically, in order to "register" under a particular namespace.  Once registered, the API offers ways to discover peers, and enumerate details of peers.

Full details of this solution are defined in the [ccnx-ldplib FSD](https://github.com/IoTone/ccnx-ldplib/blob/master/docs/ccnx-ldplib-fsd.md).

Changelog
=========

* New in 0.9.0.1 *

- refs #6 Add working test cases to validate the implementation of the public api
- refs #4 Add basic API implementation, add private utility methods, and refactor headers
- refs #5 Add makefile for test case + a README to assist in building
- refs #9 Add android build (won't need this until I have a real project to build)
- refs #7 Add Makefile build
- refs #3 Update spec for Access Control Details, improve system overview
- refs #1 Add a spec

Attributions
============

- PARC for their years of work and research on CCNx
- Google for the good Google Test framework
- Razortooth Communications, LLC for supporting the Android version of the CCNx services, called CCNx TxRxRelay