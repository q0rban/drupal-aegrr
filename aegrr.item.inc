<?php
// $Id$

class aegrrItem {
  var $values = array();

  function __contsruct($values) {
    self::setValues($values);
  }

  public function setValues($values = null) {
    $this->values = $values;
  }

  function default_values() {
    return NULL;
  }

  /**
   * Should return an array of form elements.
   */
  function form(&$form, $node) {}

  function validate(&$form, $node) {}

  /**
   * Should return an array of $settings.
   */
  function render(&$conf) {}
}

class aegrrReverseProxyItem extends aegrrItem {
  function default_values() {
    return FALSE;
  }

  function form(&$form, $node) {
    return array(
      '#type' => 'checkbox',
      '#title' => t('Reverse Proxy'),
      '#default_value' => isset($this->values) ? $this->values : $this->default_values(),
    );
  }

  function render(&$conf) {
    if ($this->values) {
      $conf['reverse_proxy'] = TRUE;
      $conf['reverse_proxy_addresses'] = array('127.0.0.1');
    }
  }
}

class aegrrOpcodeCache extends aegrrItem {
  function form(&$form, $node) {
    return array(
      '#type' => 'radios',
      '#title' => t('Opcode Cache'),
      '#default_value' => isset($this->values) ? $this->values : $this->default_values(),
      '#options' => array(
        'memcache' => t('Memcache'),
        'apc' => t('APC'),
      ),
    );
  }

  function render() {
    
  }
}