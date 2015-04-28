<?php

/**
 * @file
 * Contains the Views Parity Row row style plugin.
 */

/**
 * Plugin which performs a node_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 *
 * @ingroup views_row_plugins
 */
class views_parity_row_plugin_row_node_parity_view extends views_plugin_row_node_view {

  function option_definition() {
    $options = parent::option_definition();

    $options['views_parity_row_enable'] = array('default' => FALSE, 'bool' => TRUE);
    $options['views_parity_row']['frequency'] = array('default' => '2');
    $options['views_parity_row']['start'] = array('default' => '0');
    $options['views_parity_row']['end'] = array('default' => '0');
    $options['views_parity_row']['view_mode'] = array('default' => 'teaser');

    return $options;
  }

  function summary_title() {
    if ($this->options['views_parity_row_enable'] == TRUE) {
      $options = $this->options_form_summary_options();
      return check_plain($options[$this->options['view_mode']] . ' | ' . $this->options['views_parity_row']['frequency'] . ' | ' . $options[$this->options['views_parity_row']['view_mode']]);
    } else {
      return parent::summary_title();
    }
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['views_parity_row_enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Alternate with a different view mode every X rows ?'),
      '#default_value' => $this->options['views_parity_row_enable'],
    );

    $form['views_parity_row'] = array(
      '#type' => 'fieldset',
      '#title' => t('Configuration of Views Parity Row'),
      '#states' => array(
        'visible' => array(
          ':input[name="row_options[views_parity_row_enable]"]' => array('checked' => TRUE),
        ),
      ),
      'frequency' => array(
        '#type' => 'textfield',
        '#title' => t('Frequency of view mode change.'),
        '#description' => t('Chose a positive integer number. This number will be the frequency of change of the content view mode. Example, if you chose <em>3</em>, it means that every 3 rows, the content will use the other View mode.'),
        '#size' => 6,
        '#maxlength' => 6,
        '#default_value' => $this->options['views_parity_row']['frequency'],
        '#element_validate' => array('element_validate_integer_positive')
      ),
      'start' => array(
        '#type' => 'textfield',
        '#title' => t('Start'),
        '#description' => t('Start at which row ?'),
        '#size' => 6,
        '#maxlength' => 6,
        '#default_value' => $this->options['views_parity_row']['start'],
        '#element_validate' => array('element_validate_integer')
      ),
      'end' => array(
        '#type' => 'textfield',
        '#title' => t('End'),
        '#description' => t('End at which row ? Set <em>0</em> to disable.'),
        '#size' => 6,
        '#maxlength' => 6,
        '#default_value' => $this->options['views_parity_row']['end'],
        '#element_validate' => array('element_validate_integer')
      ),
      'view_mode' => array(
        '#type' => 'select',
        '#options' => $this->options_form_summary_options(),
        '#title' => t('Alternate view mode'),
        '#default_value' => $this->options['views_parity_row']['view_mode'],
      ),
    );
  }

  function render($row) {
    if (isset($this->nodes[$row->{$this->field_alias}])) {
      $node = $this->nodes[$row->{$this->field_alias}];
      $node->view = $this->view;
      $view_mode = $this->options['view_mode'];

      if ($this->options['views_parity_row_enable'] == TRUE) {
        $view_mode_override = FALSE;
        if ($this->view->row_index >= $this->options['views_parity_row']['start']) {
          if ($this->options['views_parity_row']['end'] != 0) {
            if ($this->view->row_index <= $this->options['views_parity_row']['end']) {
              $view_mode_override = TRUE;
            }
          } else {
            $view_mode_override = TRUE;
          }
        }

        if ($view_mode_override == TRUE) {
          if ($this->view->row_index % $this->options['views_parity_row']['frequency'] == 0) {
            $view_mode = $this->options['views_parity_row']['view_mode'];
          }
        }
      }

      $build = node_view($node, $view_mode);

      return drupal_render($build);
    }
  }
}
