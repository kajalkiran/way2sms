CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Module Details
 * Recommended modules
 * Installation
 * Configuration
 * Troubleshooting
 * Maintainers


INTRODUCTION
------------

Way2SMS module with integration with rules module provides free SMS
service to users in India using way2SMS API.

MODULE DETAILS
--------------

This module uses way2SMS API in which it requires a sender's phone
number which should be registered at way2SMS(http://site24.way2sms.com/)
before using this module. The same phone number and password is used
to trigger the API. The receiver's phone number(may not be registered at
way2SMS) and message is configurable and can be used as per the use of
the user of the module.

RECOMMENDED MODULES
-------------------

* Libraries (https://www.drupal.org/project/libraries)
  This is a dependencies for way2SMS inorder to check the way2SMS API.

* Rules (https://www.drupal.org/project/rules)
  This is a dependencies for way2SMS as the way2SMS API is triggered with
  event, SMS action.

INSTALLATION
-------------

* Download the way2SMS module.
* Downlaod way2SMS API from (https://github.com/kingster/Way2SMS-API)
  and place it in sites/all/libraries/way2sms.
* Enable the module.

CONFIGURATION
-------------
* Configure sender's phone number and password at /admin/config/services/way2sms.
* Add rule action Send SMS for the event you want the SMS to be sent.
* Add phone number field to user account.


TROUBLESHOOTING
---------------

Way2SMS works only on the correct Sender's phone number and password and
the API correctly downloaded and placed in libraries directory.
In case the module is not working, please check :
* /admin/config/services/way2sms - for correct credentials.
* Check the action for which you are triggering the SMS service.
* Clear cache with change in rules.
* Reinstall the module after disable and uninstallation.

MAINTAINERS
-----------

Current maintainers:

 * Kajal Kiran (https://www.drupal.org/u/kajalkiran)


This project has been sponsored by:
 * QED42
  QED42 is a web development agency focussed on helping organisations and
  individuals reach their potential, most of our work is in the space of
  publishing, e-commerce, social and enterprise.
