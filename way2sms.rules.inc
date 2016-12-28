<?php
/**
 * @file
 * Way2SMS Rules code : actions.
 */

/**
 * Implements hook_rules_action_info().
 *
 * Declares any meta-data about actions for rules.
 */
function way2sms_rules_action_info() {
  $actions = array(
    'way2sms_send_sms' => array(
      'label' => t('Send SMS'),
      'group' => t('Wasy2SMS'),
      'parameter' => array(
        '$reciever_contact_field' => array(
          'type' => 'text',
          'label' => t("Reciever's Contact Number."),
        ),
        '$recievers_message' => array(
          'type' => 'text',
          'label' => t('Message for reciever'),
        ),
      ),
    ),
  );
  return $actions;
}

/**
 * The action function for 'way2sms_send_sms'.
 */
function way2sms_send_sms($reciever_contact_field, $recievers_message) {
  // Path for way2SMS API.
  $lib_path = function_exists('libraries_get_path') ? libraries_get_path('way2sms') : 'sites/all/libraries/way2sms';
  $platform = $lib_path . '/way2sms-api.php';
  try {
    include $platform;
    if (!function_exists('sendWay2SMS') && !@include($platform)) {
      // Log error.
      watchdog('way2sms', 'Error Loading Way2SMS Library', [], WATCHDOG_ERROR);
      return NULL;
    }
    else {
      // Parse Receiver's Contact Field.
      $reciever_contact_field = _way2sms_preprocess_contact_field($reciever_contact_field);
      $result = NULL;

      if ($reciever_contact_field && $recievers_message) {
        // Get Sender's Phone number.
        $sender_phone_number = variable_get('way2sms_senders_phone_number');
        $sender_phone_number = _way2sms_preprocess_contact_field($sender_phone_number);
        // Get Sender's Password of way2sms.
        $sender_password = variable_get('way2sms_senders_password');

        if ($sender_phone_number && $sender_password) {
          // Call to sendWay2SMS for sending SMS.
          $result = sendWay2SMS($sender_phone_number, $sender_password, $reciever_contact_field, $recievers_message);
        }
        else {
          watchdog('way2sms', 'Invalid way2sms_senders_phone_number: @num and password', ['@num' => $way2sms_senders_phone_numbe], WATCHDOG_ERROR);
        }
      }

      else {
        watchdog('way2sms', 'Invalid reciever_contact_field : @num with message : @msg', ['@num' => $reciever_contact_field, '@msg' => $recievers_message], WATCHDOG_ERROR);
      }

      // Parse result.
      if ($result[0] && !$result[0]['result']) {
        watchdog('way2sms', 'Error sending message to reciever_contact_field : @num with message : @msg', ['@num' => $reciever_contact_field, '@msg' => $recievers_message], WATCHDOG_ERROR);
      }
    }
  }
  catch (Exception $e) {
    watchdog('way2sms', 'Error Loading Way2SMS Library', [], WATCHDOG_ERROR);
  }
}

/**
 * Parse Receiver's Contact Field.
 */
function _way2sms_preprocess_contact_field($contact_number) {
  $contact_number = trim($contact_number);
  // Check if contact_number is greater than 10 digits.
  if (strlen($contact_number) == 10) {
    return $contact_number;
  }

  // Check for +91 at the beginning.
  $contact_number = preg_replace('/\A\+91/', '', $contact_number);

  // Check for non-digit characters.
  $contact_number = preg_replace('/\D/', '', $contact_number);

  // Check for 0 at the beginning.
  $contact_number = preg_replace('/\A0/', '', $contact_number);

  if (strlen($contact_number) == 10) {
    return $contact_number;
  }
  else {
    drupal_set_message(t("Invalid Contact Number: @num", ['@num' => $contact_number]), 'error');
    return FALSE;
  }
}
