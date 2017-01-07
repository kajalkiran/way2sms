<?php

/**
 * @file
 * Way2SMS Rules code : actions.
 */

/**
 * Implements hook_rules_action_info().
 *
 * Declares way2SMS actions for rules.
 */
function way2sms_rules_action_info() {
  $actions = array(
    'way2sms_send_sms' => array(
      'label' => t('Send SMS'),
      'group' => t('Way2SMS'),
      'parameter' => array(
        'reciever_contact_field' => array(
          'type' => 'text',
          'label' => t("Reciever's Contact Number."),
        ),
        'recievers_message' => array(
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
 *
 * Send SMS via way2SMS.
 *
 * @param int $reciever_contact_field
 *   Reciever's contact number to which SMS would be sent.
 * @param string $recievers_message
 *   Message to be sent to via way2SMS.
 */
function way2sms_send_sms($reciever_contact_field, $recievers_message) {
  $result = _way2sms_send(
    variable_get('way2sms_senders_phone_number'),
    variable_get('way2sms_senders_password'),
    $reciever_contact_field,
    $recievers_message
  );

  // Parse result.
  if (empty($result[0]['result'])) {
    watchdog('way2sms', 'Error sending message to reciever_contact_field : @num with message : @msg', ['@num' => $reciever_contact_field, '@msg' => $recievers_message], WATCHDOG_ERROR);
  }
}
