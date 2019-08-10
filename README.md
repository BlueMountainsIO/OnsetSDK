#### Windows
Add folder "include" to VC++ Directories -> Include Directories
Add folder "lib" to VC++ Directoriers -> Library Directories
Add "Lua.lib" and "HorizonServer.lib" to Linker -> Input
Set C/C++ -> Language -> C++ Language Standard to "ISO C++17 Standard"

Output as Dynamic Link Library (".dll")


#### Linux
Compiler flags: -m64 -fPIC -std=gnu++17
Linker flags: -shared
Link libluaplugin.a

Output as shared object (".so")

### OPEN SOURCE LICENSE NOTICE FOR USE WITH ONSET
-------
This Open Source License (“License”) applies to any use by you of the source and object code for the video game with 
the title Onset (“Game”) as provided here by Blue Mountains GmbH (“we,” “us,” or “our”), including any code 
created prior or after this date, (“Code”) and any derivatives of the Code (“Derivatives”) as well as any source and 
object code from a contributor embedded in the Code or the Derivatives (“Contributor Code”) (the Code, 
Derivatives, and Contributor Code, collectively, the “Licensed Code”).

By using the Licensed Code you agree to and are legally bound by the terms and conditions of this License. If you do 
not agree to the terms and conditions of this License, do not use the Licensed Code and any use of the Licensed 
Code outside of the terms and Conditions of the License is an infringement of the Licensed Code.

Grant. We grant you the worldwide, revocable, royalty-free, and nonsublicensable, rights to use the Licensed Code 
as follows: To reproduce, modify, display, perform, sublicense and distribute the Licensed Code solely to use the 
Licensed Code with and within the Game. (“Grant”) This Grant does not permit you to use our trade names, 
trademarks, service marks, or names, except as required for reasonable and customary use in describing the origin of 
the Licensed Content and reproducing the content of the copyright notice below. Nothing in this License shall be 
construed to grant you any ownership whatsoever in the Licensed Code and the property and intellectual property 
contained therein.

Obligations. The Grant is subject to your express compliance with the following obligations: 

*	Attribution. Notice: You shall keep intact all copyright, patent or trademarks notices and all notices that refer to 
the License and to the disclaimer of warranties. You shall include a copy of such notices and a copy of the 
License with every copy of the Licensed Code you distribute or communicate as follows:

Copyright (C) 2019 Blue Mountains GmbH

This program is free software: you can redistribute it and/or modify it under the terms of the Onset Open Source 
License as published by Blue Mountains GmbH.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Onset Open Source 
License for more details. 

You should have received a copy of the Onset Open Source License along with this program. If not, see <[URL]>.

*	Copyleft: If you distribute or communicate copies of the Licensed Code, this distribution or communication will 
be done under the terms of this License or of a later version of this License, unless the Licensed Content is 
expressly distributed only under this version of the License. You cannot offer or impose any additional terms or 
conditions on the Licensed Content that alter or restrict the terms of the License.

*	Provision of Source Code: When distributing or communicating copies of the Licensed Code, you shall provide a 
machine-readable copy of the source code or indicate a repository where this source code easily and freely is 
available for as long as you continue to distribute or communicate the Licensed Content.

NO WARRANTIES. LICSENSED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS'' BASIS, WITHOUT WARRANTY 
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE LICENSED 
CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE OR NON-INFRINGING. THE ENTIRE 
RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED SOFTWARE IS WITH YOU. SHOULD THE LICENSED 
CONTET PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT US, OUR LICENSORS OR AFFILIATES OR ANY OTHER 
CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE OF THE LICENSED CONTENT IS AUTHORIZED 
HEREUNDER EXCEPT UNDER THIS DISCLAIMER.

LIMITATION OF LIABILITY. UNDER NO CIRCUMSTANCES AND UNDER NO LEGAL THEORY, WHETHER TORT (INCLUDING 
NEGLIGENCE), CONTRACT, OR OTHERWISE, SHALL YOU, US, ANY OTHER CONTRIBUTOR, OR ANY DISTRIBUTOR OF 
THE LICENSED CODE, OR ANY SUPPLIER OF ANY OF SUCH PARTIES, BE LIABLE TO ANY PERSON FOR ANY INDIRECT, 
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES OF ANY CHARACTER INCLUDING, WITHOUT LIMITATION, 
DAMAGES FOR LOSS OF GOODWILL, WORK STOPPAGE, COMPUTER FAILURE OR MALFUNCTION, OR ANY AND ALL 
OTHER COMMERCIAL DAMAGES OR LOSSES, EVEN IF SUCH PARTY SHALL HAVE BEEN INFORMED OF THE POSSIBILITY 
OF SUCH DAMAGES. THIS LIMITATION OF LIABILITY SHALL NOT APPLY TO LIABILITY FOR DEATH OR PERSONAL INJURY 
RESULTING FROM SUCH PARTY'S GROSS NEGLIGENCE TO THE EXTENT APPLICABLE LAW PROHIBITS SUCH 
LIMITATION. SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR LIMITATION OF INCIDENTAL OR 
CONSEQUENTIAL DAMAGES, BUT MAY ALLOW LIABILITY TO BE LIMITED; IN SUCH CASES, A PARTY'S, ITS EMPLOYEES, 
LICENSORS OR AFFILIATES' LIABILITY SHALL BE LIMITED TO U.S. $50. 

Nothing contained in this License shall prejudice the statutory rights of any party dealing as a consumer.

Term. This License and the rights granted hereunder will terminate automatically if you fail to comply with terms 
herein and fail to cure such breach within 30 days of becoming aware of the breach. All sublicenses to the Licensed 
Content which are properly granted shall survive any termination of this License. Provisions which, by their nature, 
must remain in effect beyond the termination of this License shall survive.

Miscellaneous. This License represents the complete agreement concerning the subject matter hereof. All rights in 
the Licensed Content not expressly granted under this License are reserved. We may amend the Licensed Code and 
or the License at any time at our convenience. This License is governed by the laws of Germany, excluding its 
conflict-of-law provisions. All disputes arising from or relating to this Agreement shall be heard by the state and 
federal courts in Munich, Germany. If any part of this Agreement is found void and unenforceable, it will not affect 
the validity of the balance of the Agreement, which shall remain valid and enforceable according to its terms. 

UPDATE: 2019-08-02

VERSION: 1.0
