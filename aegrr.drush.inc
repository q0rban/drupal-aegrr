<?php
// $Id$

/**
 * Map values of site node into command line arguments
 */
function drush_aegrr_pre_hosting_task($task) {
  $task =& drush_get_context('HOSTING_TASK');

  if ($task->ref->type == 'site') {
    $task->options['aegrr'] = $task->ref->aegrr->conf;
  }
}

/**
 * Implementation of hook_provision_drupal_config().
 */
function aegrr_provision_drupal_config($url, $options) {
  $output = '';

  if (isset($options['aegrr'])) {
    $output .= "// AeGrr!\n";
    foreach($options['aegrr'] as $key => $val) {
      $output .= '  $conf[\''. $key .'\'] = '. aegrr_var_export($val, '  ') .";\n";
    }
    $output .= "// End AeGrr.\n\n";
  }

  return $output;
}

/**
 * Export var function -- from Views.
 */
function aegrr_var_export($var, $prefix = '', $init = TRUE) {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "  '$key' => " . aegrr_var_export($value, '  ', FALSE) . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  else if (is_string($var) && strpos($var, "\n") !== FALSE) {
    // Replace line breaks in strings with a token for replacement
    // at the very end. This protects whitespace in strings from
    // unintentional indentation.
    $var = str_replace("\n", "***BREAK***", $var);
    $output = var_export($var, TRUE);
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  if ($init) {
    $output = str_replace("***BREAK***", "\n", $output);
  }

  return $output;
}