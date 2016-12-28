<?php
/**
 * @file
 * Way2SMS Configuration form settings.
 */

/**
 * Configuration form to set
 * Sender's phone number and password
 * same as way2sms account.
 */
function way2sms_form($form, &$form_state) {

  $form['way2sms_senders_phone_number'] = array(
    '#type' => 'textfield',
    '#title' => t("Sender's contact number"),
    '#description' => t('Enter the registered contact number at way2sms. For example: 7722800915. Note: Do not use +91, 0.'),
    '#default_value' => variable_get('way2sms_senders_phone_number'),
    '#size' => 10,
    '#maxlength' => 13,
    '#required' => TRUE,
  );
  $form['way2sms_senders_password'] = array(
    '#type' => 'password',
    '#title' => t('Way2SMS account password'),
    '#description' => t('Enter login password as your way2sms password. Note: You need to have an account to way2sms.'),
    '#size' => 10,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
