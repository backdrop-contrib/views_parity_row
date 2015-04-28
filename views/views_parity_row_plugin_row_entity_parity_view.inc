<?php

/**
 * @file
 * Contains the Views Parity Row for entities row style plugin.
 */

/**
 * Plugin which performs a node_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 *
 * @ingroup views_row_plugins
 */
class views_parity_row_plugin_row_entity_parity_view extends entity_views_plugin_row_entity_view {
  /**
   * @return array
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['views_parity_row_enable'] = array('default' => FALSE, 'bool' => TRUE);
    $options['views_parity_row']['frequency'] = array('default' => '2');
    $options['views_parity_row']['start'] = array('default' => '0');
    $options['views_parity_row']['end'] = array('default' => '0');
    $options['views_parity_row']['view_mode'] = array('default' => 'teaser');

    return $options;
  }

  /**
   * Return the main options, which are shown in the summary title.
   */
  function options_form_summary_options() {
    $entity_info = entity_get_info($this->entity_type);
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }
    if (empty($options)) {
      $options = array(
        'teaser' => t('Teaser'),
        'full' => t('Full content')
      );
    }

    return $options;
  }

  function summary_title() {
    $options = $this->options_form_summary_options();
    if ($this->options['views_parity_row_enable'] == TRUE) {
      $string = $options[$this->options['view_mode']] . ' | ' . $this->options['views_parity_row']['frequency'] . ' | ' . $options[$this->options['views_parity_row']['view_mode']];
    }
    else {
      $string = $options[$this->options['view_mode']];
    }
    return check_plain($string);
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

  public function pre_render($values) {
    if (!empty($values)) {
      list($this->entity_type, $this->entities) = $this->view->query->get_result_entities($values, !empty($this->relationship) ? $this->relationship : NULL, isset($this->field_alias) ? $this->field_alias : NULL);
    }
  }

  public function render($values) {
    if ($entity = $this->get_value($values)) {
      $entity->view = $this->view;
      $view_mode = $this->options['view_mode'];

      if ($this->options['views_parity_row_enable'] == TRUE) {
        $view_mode_override = FALSE;
        if ($this->view->row_index >= $this->options['views_parity_row']['start']) {
          if ($this->options['views_parity_row']['end'] != 0) {
            if ($this->view->row_index <= $this->options['views_parity_row']['end']) {
              $view_mode_override = TRUE;
            }
          }
          else {
            $view_mode_override = TRUE;
          }
        }

        if ($view_mode_override == TRUE) {
          if ($this->view->row_index-$this->options['views_parity_row']['start'] % $this->options['views_parity_row']['frequency'] == 0) {
            $view_mode = $this->options['views_parity_row']['view_mode'];
          }
        }
      }

      $render = entity_view($this->entity_type, array($entity), $view_mode);

      return drupal_render($render);
    }
  }
}

