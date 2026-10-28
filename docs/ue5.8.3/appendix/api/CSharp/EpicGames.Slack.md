# CSharp / EpicGames.Slack

- project root: `Source/Programs/Shared/EpicGames.Slack`
- files: 26; symbols: 318
- symbol kinds: class=58, const=11, ctor=36, enum=2, enumerator=6, field=3, interface=2, method=47, operator=4, property=149
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Slack/Block.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Block`  
`public abstract class Block`  
_public; L14-37_
- attrs: `[JsonConverter(typeof(BlockConverter))]`
- desc: Abstract base class for all BlockKit blocks to derive from.
- L20 _public property_ `public string Type { get; }` — attrs: `[JsonPropertyName("type"), JsonPropertyOrder(0)]` — The block type
- L27 _public property_ `public string? BlockId { get; set; }` — attrs: `[JsonPropertyName("block_id"), JsonPropertyOrder(30)]` — A string acting as a unique identifier for a block. If not specified, one will be generated. Maximum length for this field is 255 characters. block_id should be unique for each message and each iteration of a message. If a message is updated, use a new block_id.
- L33-36 _protected ctor_ `protected Block(string type)` — Constructor

#### interface `EpicGames.Slack.ISlackBlockContainer`  
`public interface ISlackBlockContainer`  
_public; L42-48_
- desc: Interface for a container of Block items
- L47 _public* property_ `List<Block> Blocks { get; }` — List of blocks

#### class `EpicGames.Slack.BlockConverter`  
`class BlockConverter : JsonConverter<Block>`  
_internal*; L53-64_
- inherits: `JsonConverter<Block>`
- desc: Polymorphic serializer for Block objects.
- L55-58 _public method_ `public override Block? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L60-63 _public method_ `public override void Write(Utf8JsonWriter writer, Block value, JsonSerializerOptions options)`

### `Source/Programs/Shared/EpicGames.Slack/Blocks/ActionsBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.ActionsBlock`  
`public class ActionsBlock : Block, ISlackElementContainer`  
_public; L12-26_
- inherits: `Block, ISlackElementContainer`
- desc: A block that is used to hold interactive Element objects.
- L18 _public property_ `public List<Element> Elements { get; }` — attrs: `[JsonPropertyName("elements"), JsonPropertyOrder(1)]` — A collection of interactive elements.
- L23-25 _public ctor_ `public ActionsBlock() : base("actions")` — Constructor

#### class `EpicGames.Slack.Blocks.ActionsBlockExtensions`  
`public static class ActionsBlockExtensions`  
_public; L31-55_
- desc: Extension methods for Block
- L37-42 _public method_ `public static ActionsBlock AddActions(this ISlackBlockContainer container)` — Add an ActionsBlock to the list of blocks
- L49-54 _public method_ `public static void AddActions(this ISlackBlockContainer container, Action<ActionsBlock> configure)` — Add an ActionsBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/ContextBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.ContextBlock`  
`public class ContextBlock : Block`  
_public; L13-27_
- inherits: `Block`
- desc: Displays message context, which can include both images and text.
- L19 _public property_ `public List<Element> Elements { get; }` — attrs: `[JsonPropertyName("elements")]` — An array of image elements and text objects. Maximum number of items is 10.
- L24-26 _public ctor_ `public ContextBlock() : base("context")` — Constructor

#### class `EpicGames.Slack.Blocks.ContextBlockExtensions`  
`public static class ContextBlockExtensions`  
_public; L32-58_
- desc: Extension methods for Block
- L39-44 _public method_ `public static void AddContext(this ISlackBlockContainer container, Action<ContextBlock> configure)` — Add an ContextBlock to the list of blocks
- L51-57 _public method_ `public static ContextBlock AddContext(this ISlackBlockContainer container, TextObject text)` — Add an ContextBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/DividerBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.DividerBlock`  
`public class DividerBlock : Block`  
_public; L8-16_
- inherits: `Block`
- desc: A content divider, like an <hr>, to split up different blocks inside of a message. The divider block is nice and neat, requiring only a type.
- L13-15 _public ctor_ `public DividerBlock() : base("divider")` — Constructor

#### class `EpicGames.Slack.Blocks.DividerBlockExtensions`  
`public static class DividerBlockExtensions`  
_public; L21-32_
- desc: Extension methods for Block
- L27-31 _public method_ `public static void AddDivider(this ISlackBlockContainer container)` — Add an DividerBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/HeaderBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.HeaderBlock`  
`public class HeaderBlock : Block`  
_public; L11-35_
- inherits: `Block`
- desc: A header is a plain-text block that displays in a larger, bold font. Use it to delineate between different groups of content in your app's surfaces.
- L17 _public property_ `public PlainTextObject Text { get; }` — attrs: `[JsonPropertyName("text"), JsonPropertyOrder(1)]` — The text for the block, in the form of a plain_text text object. Maximum length for the text in this field is 150 characters.
- L23-26 _public ctor_ `public HeaderBlock(PlainTextObject text) : base("header")` — Constructor
- L32-34 _public ctor_ `public HeaderBlock(string text) : this(new PlainTextObject(text))` — Constructor

#### class `EpicGames.Slack.Blocks.HeaderBlockExtensions`  
`public static class HeaderBlockExtensions`  
_public; L40-60_
- desc: Extension methods for Block
- L47-51 _public method_ `public static void AddHeader(this ISlackBlockContainer container, PlainTextObject text)` — Add an HeaderBlock to the list of blocks
- L59 _public method_ `public static void AddHeader(this ISlackBlockContainer container, string text, bool? emoji)` — Add an HeaderBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/ImageBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.ImageBlock`  
`public class ImageBlock : Block`  
_public; L12-41_
- inherits: `Block`
- desc: A simple image block, designed to make those cat photos really pop.
- L18 _public property_ `public Uri ImageUrl { get; set; }` — attrs: `[JsonPropertyName("image_url"), JsonPropertyOrder(1)]` — The URL of the image to be displayed.Maximum length for this field is 3000 characters.
- L24 _public property_ `public string AltText { get; set; }` — attrs: `[JsonPropertyName("alt_text"), JsonPropertyOrder(2)]` — A plain-text summary of the image.This should not contain any markup.Maximum length for this field is 2000 characters.
- L30 _public property_ `public PlainTextObject? Title { get; set; }` — attrs: `[JsonPropertyName("title"), JsonPropertyOrder(3)]` — An optional title for the image in the form of a text object that can only be of type: plain_text. Maximum length for the text in this field is 2000 characters.
- L35-40 _public ctor_ `public ImageBlock(Uri imageUrl, string altText, PlainTextObject? title = null) : base("image")` — Constructor

#### class `EpicGames.Slack.Blocks.ImageBlockExtensions`  
`public static class ImageBlockExtensions`  
_public; L46-56_
- desc: Extension methods for ImageBlock
- L51-55 _public method_ `public static void AddImage(this ISlackBlockContainer container, Uri imageUrl, string altText, PlainTextObject? title = null)` — Add an ImageBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/InputBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.InputBlock`  
`public class InputBlock : Block`  
_public; L11-51_
- inherits: `Block`
- desc: A block that collects information from users - it can hold a plain-text input element, a checkbox element, a radio button element, a select menu element, a multi-select menu element, or a datepicker.
- L17 _public property_ `public PlainTextObject Label { get; set; }` — attrs: `[JsonPropertyName("label"), JsonPropertyOrder(1)]` — A label that appears above an input element in the form of a text object that must have type of plain_text. Maximum length for the text in this field is 2000 characters.
- L23 _public property_ `public Element Element { get; set; }` — attrs: `[JsonPropertyName("element"), JsonPropertyOrder(2)]` — A plain-text input element, a checkbox element, a radio button element, a select menu element, a multi-select menu element, or a datepicker.
- L29 _public property_ `public bool? DispatchAction { get; set; }` — attrs: `[JsonPropertyName("dispatch_action"), JsonPropertyOrder(3)]` — A boolean that indicates whether or not the use of elements in this block should dispatch a block_actions payload. Defaults to false.
- L35 _public property_ `public PlainTextObject? Hint { get; set; }` — attrs: `[JsonPropertyName("hint"), JsonPropertyOrder(4)]` — An optional hint that appears below an input element in a lighter grey. It must be a text object with a type of plain_text. Maximum length for the text in this field is 2000 characters.
- L41 _public property_ `public bool? Optional { get; set; }` — attrs: `[JsonPropertyName("optional"), JsonPropertyOrder(5)]` — A boolean that indicates whether the input element may be empty when a user submits the modal. Defaults to false.
- L46-50 _public ctor_ `public InputBlock(PlainTextObject label, Element element) : base("input")` — Constructor

#### class `EpicGames.Slack.Blocks.InputBlockExtensions`  
`public static class InputBlockExtensions`  
_public; L56-67_
- desc: Extension methods for InputBlock
- L61-66 _public method_ `public static InputBlock AddInput(this ISlackBlockContainer container, PlainTextObject label, Element element)` — Add an ImageBlock to the list of blocks

### `Source/Programs/Shared/EpicGames.Slack/Blocks/MarkdownBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.MarkdownBlock`  
`public class MarkdownBlock : Block`  
_public; L10-26_
- inherits: `Block`
- desc: Represents a BlockKit Markdown block
- L16 _public property_ `public string Text { get; set; }` — attrs: `[JsonPropertyName("text"), JsonPropertyOrder(1)]` — The standard markdown-formatted text. The cumulative limit for all markdown blocks in a single payload is 12,000 characters.
- L22-25 _public ctor_ `public MarkdownBlock(string text) : base("markdown")` — Constructor

#### class `EpicGames.Slack.Blocks.MarkdownBlockExtensions`  
`public static class MarkdownBlockExtensions`  
_public; L31-43_
- desc: Extension methods for MarkdownBlock
- L38-42 _public method_ `public static void AddMarkdown(this ISlackBlockContainer container, string text)` — Adds a new MarkdownBlock with the given text element to the container. The block container to add the markdown to The text content to populate the markdown with

### `Source/Programs/Shared/EpicGames.Slack/Blocks/SectionBlock.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Blocks.SectionBlock`  
`public class SectionBlock : Block`  
_public; L12-54_
- inherits: `Block`
- desc: Represents a BlockKit Section block
- L18 _public property_ `public TextObject? Text { get; set; }` — attrs: `[JsonPropertyName("text"), JsonPropertyOrder(1)]` — The text for the block, in the form of a text object. Maximum length for the text in this field is 3000 characters.
- L25 _public property_ `public IReadOnlyList<TextObject>? Fields { get; set; }` — attrs: `[JsonPropertyName("fields"), JsonPropertyOrder(2)]` — Required if no text is provided. An array of text objects. Any text objects included with fields will be rendered in a compact format that allows for 2 columns of side-by-side text. Maximum number of items is 10. Maximum length for the text in each item is 2000 characters.
- L31 _public property_ `public Element? Accessory { get; set; }` — attrs: `[JsonPropertyName("accessory"), JsonPropertyOrder(3)]` — One of the available element objects.
- L38-42 _public ctor_ `public SectionBlock(TextObject text, Element? accessory = null) : base("section")` — Constructor
- L49-53 _public ctor_ `public SectionBlock(List<TextObject> fields, Element? accessory = null) : base("section")` — Constructor

#### class `EpicGames.Slack.Blocks.SectionBlockExtensions`  
`public static class SectionBlockExtensions`  
_public; L59-82_
- desc: Extension methods for SectionBlock
- L66-70 _public method_ `public static void AddSection(this ISlackBlockContainer container, TextObject text)` — Adds a new SectionBlock with a single text element to the container. The block container to add the section to The text content to populate the section with
- L77-81 _public method_ `public static void AddSection(this ISlackBlockContainer container, List<TextObject> fields)` — Adds a new SectionBlock with multiple field elements to the container The block container to add the section to The list of text fields to populate the section with

### `Source/Programs/Shared/EpicGames.Slack/Element.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Element`  
`public abstract class Element`  
_public; L14-30_
- attrs: `[JsonConverter(typeof(ElementConverter))]`
- desc: Abstract base class for all BlockKit elements to derive from.
- L20 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("type"), JsonPropertyOrder(0)]` — Type of the element
- L26-29 _protected ctor_ `protected Element(string type)` — Constructor

#### interface `EpicGames.Slack.ISlackElementContainer`  
`public interface ISlackElementContainer`  
_public; L35-41_
- desc: Something that contains a list of elements. Used for extension methods.
- L40 _public property_ `public List<Element> Elements { get; }` — List of elements in this container

#### class `EpicGames.Slack.ElementConverter`  
`class ElementConverter : JsonConverter<Element>`  
_internal*; L46-57_
- inherits: `JsonConverter<Element>`
- desc: Polymorphic serializer for Block objects.
- L48-51 _public method_ `public override Element? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L53-56 _public method_ `public override void Write(Utf8JsonWriter writer, Element value, JsonSerializerOptions options)`

### `Source/Programs/Shared/EpicGames.Slack/Elements/ButtonElement.cs` (EpicGames.Slack)


#### enum `EpicGames.Slack.Elements.ButtonStyle`  
`public enum ButtonStyle`  
_public; L14-25_
- attrs: `[JsonConverter(typeof(ButtonStyleJsonConverter))]`
- desc: Determines the visual color scheme to use for the button.
- L19 _public* enumerator_ `Primary` — Used for affirmation/confirmation actions.
- L24 _public* enumerator_ `Danger` — Used when an action is destructive and cannot be undone.

#### class `EpicGames.Slack.Elements.ButtonStyleJsonConverter`  
`class ButtonStyleJsonConverter : JsonConverter<ButtonStyle>`  
_internal*; L30-51_
- inherits: `JsonConverter<ButtonStyle>`
- desc: Json serializer for ButtonStyle
- L32-35 _public method_ `public override ButtonStyle Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L37-50 _public method_ `public override void Write(Utf8JsonWriter writer, ButtonStyle value, JsonSerializerOptions options)`

#### class `EpicGames.Slack.Elements.ButtonElement`  
`public class ButtonElement : Element`  
_public; L56-107_
- inherits: `Element`
- desc: An button element that can be added to an Blocks.ActionsBlock.
- L62 _public property_ `public PlainTextObject Text { get; }` — attrs: `[JsonPropertyName("text"), JsonPropertyOrder(1)]` — A text object that defines the button's text. Can only be of type: plain_text. text may truncate with ~30 characters. Maximum length for the text in this field is 75 characters.
- L69 _public property_ `public string? ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id"), JsonPropertyOrder(2)]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L75 _public property_ `public Uri? Url { get; set; }` — attrs: `[JsonPropertyName("url"), JsonPropertyOrder(3)]` — A URL to load in the user's browser when the button is clicked. Maximum length for this field is 3000 characters. If you're using url, you'll still receive an interaction payload and will need to send an acknowledgement response.
- L81 _public property_ `public string? Value { get; set; }` — attrs: `[JsonPropertyName("value"), JsonPropertyOrder(4)]` — The value to send along with the interaction payload. Maximum length for this field is 2000 characters.
- L87 _public property_ `public ButtonStyle? Style { get; set; }` — attrs: `[JsonPropertyName("style"), JsonPropertyOrder(5)]` — Decorates buttons with alternative visual color schemes. Use this option with restraint.
- L93 _public property_ `public string? AccessibilityLabel { get; set; }` — attrs: `[JsonPropertyName("accessibility_label"), JsonPropertyOrder(6)]` — A label for longer descriptive text about a button element. This label will be read out by screen readers instead of the button text object. Maximum length for this field is 75 characters.
- L98-106 _public ctor_ `public ButtonElement(PlainTextObject text, Uri? url = null, string? actionId = null, string? value = null, ButtonStyle? style = null) : base("button")` — Construct a new Button action element.

#### class `EpicGames.Slack.Elements.ButtonExtensions`  
`public static class ButtonExtensions`  
_public; L112-123_
- desc: Extension methods for buttons
- L117-122 _public method_ `public static ISlackElementContainer AddButton(this ISlackElementContainer list, string text, Uri? url = null, string? actionId = null, string? value = null, ButtonStyle? style = null)` — Add a new button to the list of elements

### `Source/Programs/Shared/EpicGames.Slack/Elements/CheckboxGroupElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.CheckboxGroupElement`  
`public class CheckboxGroupElement : Element`  
_public; L11-53_
- inherits: `Element`
- desc: A checkbox group that allows a user to choose multiple items from a list of possible options.
- L18 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L24 _public property_ `public List<SlackOption> Options { get; }` — attrs: `[JsonPropertyName("options")]` — An array of option objects. A maximum of 10 options are allowed.
- L30 _public property_ `public List<SlackOption> InitialOptions { get; }` — attrs: `[JsonPropertyName("initial_options")]` — An array of option objects that exactly matches one or more of the options within options. These options will be selected when the checkbox group initially loads.
- L36 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L42 _public property_ `public bool FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L47-52 _public ctor_ `public CheckboxGroupElement(string actionId, List<SlackOption> options) : base("checkboxes")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/DatePickerElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.DatePickerElement`  
`public class DatePickerElement : Element`  
_public; L10-51_
- inherits: `Element`
- desc: An element which lets users easily select a date from a calendar style UI.
- L17 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L23 _public property_ `public PlainTextObject? Placeholder { get; set; }` — attrs: `[JsonPropertyName("placeholder")]` — A plain_text only text object that defines the placeholder text shown on the datepicker. Maximum length for the text in this field is 150 characters.
- L29 _public property_ `public string? InitialDate { get; set; }` — attrs: `[JsonPropertyName("initial_date")]` — The initial date that is selected when the element is loaded. This should be in the format YYYY-MM-DD.
- L35 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L41 _public property_ `public bool FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L46-50 _public ctor_ `public DatePickerElement(string actionId) : base("datepicker")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/OverflowMenuElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.OverflowMenuElement`  
`public class OverflowMenuElement : Element`  
_public; L15-46_
- inherits: `Element`
- desc: This is like a cross between a button and a select menu - when a user clicks on this overflow button, they will be presented with a list of options to choose from. Unlike the select menu, there is no typeahead field, and the button always appears with an ellipsis ("…") rather than customisable text. As such, it is usually used if you want a more compact layout than a select menu, or to supply a list of less visually important actions after a row of buttons. You can also specify simple URL links as overflow menu options, instead of actions.
- L22 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L28 _public property_ `public List<SlackOption> Options { get; }` — attrs: `[JsonPropertyName("options")]` — An array of up to five option objects to display in the menu.
- L34 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L39-45 _public ctor_ `public OverflowMenuElement(string actionId, List<SlackOption> options, SlackConfirm? confirm = null) : base("overflow")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/PlainTextInputElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.PlainTextInputElement`  
`public class PlainTextInputElement : Element`  
_public; L10-66_
- inherits: `Element`
- desc: A plain-text input, similar to the HTML <input> tag, creates a field where a user can enter freeform data. It can appear as a single-line field or a larger text area using the multiline flag.
- L17 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L23 _public property_ `public PlainTextObject? Placeholder { get; set; }` — attrs: `[JsonPropertyName("placeholder")]` — A plain_text only text object that defines the placeholder text shown in the plain-text input. Maximum length for the text in this field is 150 characters.
- L29 _public property_ `public string? InitialValue { get; set; }` — attrs: `[JsonPropertyName("initial_value")]` — The initial value in the plain-text input when it is loaded.
- L35 _public property_ `public bool MultiLine { get; set; }` — attrs: `[JsonPropertyName("multiline")]` — Indicates whether the input will be a single line (false) or a larger textarea (true). Defaults to false.
- L41 _public property_ `public int? MinLength { get; set; }` — attrs: `[JsonPropertyName("min_length")]` — The minimum length of input that the user must provide. If the user provides less, they will receive an error. Maximum value is 3000.
- L47 _public property_ `public int? MaxLength { get; set; }` — attrs: `[JsonPropertyName("max_length")]` — The maximum length of input that the user can provide. If the user provides more, they will receive an error.
- L53 _public property_ `public bool FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L58-65 _public ctor_ `public PlainTextInputElement(string actionId, PlainTextObject? placeholder = null, string? initialValue = null, bool multiLine = false) : base("plain_text_input")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/RadioButtonGroupElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.RadioButtonGroupElement`  
`public class RadioButtonGroupElement : Element`  
_public; L11-53_
- inherits: `Element`
- desc: A radio button group that allows a user to choose one item from a list of possible options.
- L18 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L24 _public property_ `public List<SlackOption> Options { get; }` — attrs: `[JsonPropertyName("options")]` — An array of option objects. A maximum of 10 options are allowed.
- L30 _public property_ `public SlackOption? InitialOption { get; set; }` — attrs: `[JsonPropertyName("initial_option")]` — An array of option objects that exactly matches one or more of the options within options. These options will be selected when the checkbox group initially loads.
- L36 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L42 _public property_ `public bool? FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L47-52 _public ctor_ `public RadioButtonGroupElement(string actionId, List<SlackOption> options) : base("radio_buttons")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/SelectMenuElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.SelectMenuElement`  
`public abstract class SelectMenuElement : Element`  
_public; L12-28_
- inherits: `Element`
- desc: An element which lets users easily select a date from a calendar style UI.
- L19 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L24-27 _protected ctor_ `protected SelectMenuElement(string type, string actionId) : base(type)` — Constructor

#### class `EpicGames.Slack.Elements.StaticSelectMenuElement`  
`public class StaticSelectMenuElement : SelectMenuElement`  
_public; L33-92_
- inherits: `SelectMenuElement`
- desc: This is the simplest form of select menu, with a static list of options passed in when defining the element.
- L39 _public property_ `public PlainTextObject Placeholder { get; set; }` — attrs: `[JsonPropertyName("placeholder")]` — A plain_text only text object that defines the placeholder text shown on the menu. Maximum length for the text in this field is 150 characters.
- L46 _public property_ `public List<SlackOption>? Options { get; set; }` — attrs: `[JsonPropertyName("options")] [SuppressMessage("Usage", "CA2227:Collection properties should be read only")]` — An array of option objects. A maximum of 10 options are allowed.
- L53 _public property_ `public List<SlackOptionGroup>? OptionGroups { get; set; }` — attrs: `[JsonPropertyName("option_groups")] [SuppressMessage("Usage", "CA2227:Collection properties should be read only")]` — An array of option objects. A maximum of 10 options are allowed.
- L59 _public property_ `public SlackOption? InitialOption { get; }` — attrs: `[JsonPropertyName("initial_option")]` — An array of option objects that exactly matches one or more of the options within options. These options will be selected when the checkbox group initially loads.
- L65 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L71 _public property_ `public bool FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L76-81 _public ctor_ `public StaticSelectMenuElement(string actionId, PlainTextObject placeholder, List<SlackOption> options) : base("static_select", actionId)` — Construct a new Button action element.
- L86-91 _public ctor_ `public StaticSelectMenuElement(string actionId, PlainTextObject placeholder, List<SlackOptionGroup> optionGroups) : base("static_select", actionId)` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/Elements/TextObject.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.TextObject`  
`public class TextObject : Element`  
_public; L10-45_
- inherits: `Element`
- desc: A text object
- L16 _public property_ `public string Text { get; set; }` — attrs: `[JsonPropertyName("text"), JsonPropertyOrder(1)]` — Text to render
- L22 _public property_ `public bool? Emoji { get; set; }` — attrs: `[JsonPropertyName("emoji"), JsonPropertyOrder(2)]` — Whether to show emojis in the text
- L28-30 _public ctor_ `public TextObject(string text) : this("mrkdwn", text, null)` — Constructor
- L35-39 _protected ctor_ `protected TextObject(string type, string text, bool? emoji) : base(type)` — Constructor
- L44 _public operator_ `public static implicit operator TextObject(string text)` — Implicit conversion from a regular string

#### class `EpicGames.Slack.Elements.PlainTextObject`  
`public class PlainTextObject : TextObject`  
_public; L50-63_
- inherits: `TextObject`
- desc: Plain text object
- L55-57 _public ctor_ `public PlainTextObject(string text, bool? emoji = null) : base("plain_text", text, emoji)` — Constructor
- L62 _public operator_ `public static implicit operator PlainTextObject(string text)` — Implicit conversion from a regular string

### `Source/Programs/Shared/EpicGames.Slack/Elements/TimePickerElement.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.Elements.TimePickerElement`  
`public class TimePickerElement : Element`  
_public; L10-51_
- inherits: `Element`
- desc: An element which lets users easily select a date from a calendar style UI.
- L17 _public property_ `public string ActionId { get; set; }` — attrs: `[JsonPropertyName("action_id")]` — An identifier for this action. You can use this when you receive an interaction payload to identify the source of the action. Should be unique among all other action_ids in the containing block. Maximum length for this field is 255 characters.
- L23 _public property_ `public PlainTextObject? Placeholder { get; set; }` — attrs: `[JsonPropertyName("placeholder")]` — A plain_text only text object that defines the placeholder text shown on the datepicker. Maximum length for the text in this field is 150 characters.
- L29 _public property_ `public string? InitialTime { get; set; }` — attrs: `[JsonPropertyName("initial_time")]` — The initial time that is selected when the element is loaded. This should be in the format HH:mm, where HH is the 24-hour format of an hour (00 to 23) and mm is minutes with leading zeros (00 to 59), for example 22:25 for 10:25pm.
- L35 _public property_ `public SlackConfirm? Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A confirm object that defines an optional confirmation dialog that appears after clicking one of the checkboxes in this element.
- L41 _public property_ `public bool FocusOnLoad { get; set; }` — attrs: `[JsonPropertyName("focus_on_load")]` — Indicates whether the element will be set to auto focus within the view object. Only one element can be set to true. Defaults to false.
- L46-50 _public ctor_ `public TimePickerElement(string actionId) : base("timepicker")` — Construct a new Button action element.

### `Source/Programs/Shared/EpicGames.Slack/SlackAttachment.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackAttachment`  
`public class SlackAttachment : ISlackBlockContainer`  
_public; L11-42_
- inherits: `ISlackBlockContainer`
- desc: Abstract base class for all BlockKit blocks to derive from.
- L17 _public property_ `public string Color { get; set; }` — attrs: `[JsonPropertyName("color"), JsonPropertyOrder(1)]` — The color of the line down the left side of the attachment.
- L24 _public property_ `public string? FallbackText { get; set; }` — attrs: `[JsonPropertyName("fallback"), JsonPropertyOrder(2)]` — Used for the "toast" notifications sent by Slack. If not set, and the Text property of the base message isn't set, the notification will have a message saying it has no preview.
- L30 _public property_ `public List<Block> Blocks { get; }` — attrs: `[JsonPropertyName("blocks"), JsonPropertyOrder(3)]` — A collection of BlockKit blocks the attachment is composed from.
- L36-41 _public operator_ `public static implicit operator SlackMessage(SlackAttachment attachment)` — Implicit conversion to a message of its own

### `Source/Programs/Shared/EpicGames.Slack/SlackClient.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackException`  
`public class SlackException : Exception`  
_public; L23-37_
- inherits: `Exception`
- desc: Exception thrown due to an error response from Slack
- L28 _public property_ `public string Code { get; }` — Slack error code
- L33-36 _public ctor_ `public SlackException(string code) : base(code)` — Constructor

#### enum `EpicGames.Slack.SlackErrorBehavior`  
`enum SlackErrorBehavior`  
_internal*; L42-55_
- desc: Specifies how to handle a Slack API error
- L45 _public* enumerator_ `Throw` — Throw a SlackException (caller handles logging)
- L48 _public* enumerator_ `LogError` — Log at error level, don't throw
- L51 _public* enumerator_ `LogWarning` — Log at warning level, don't throw
- L54 _public* enumerator_ `Ignore` — Don't log, don't throw

#### class `EpicGames.Slack.SlackMessageId`  
`public class SlackMessageId`  
_public; L60-89_
- desc: Response from posting a Slack message
- L65 _public property_ `public string Channel { get; set; }` — The channel id. Note that posting messages is more lenient than updating messages, and will accept a user ID as a recipient channel. The actual DM channel this resolves to will be returned in this parameter.
- L70 _public property_ `public string? ThreadTs { get; set; }` — Thread containing the message
- L75 _public property_ `public string Ts { get; set; }` — Timestamp of the message
- L80-85 _public ctor_ `public SlackMessageId(string channel, string? threadTs, string ts)` — Constructor
- L88 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Slack.SlackClient`  
`public sealed class SlackClient : IDisposable`  
_public; L94-659_
- inherits: `IDisposable`
- desc: Wrapper around Slack client functionality
- L105 _private* field_ `readonly HttpClient _httpClient`
- L106 _private* field_ `readonly JsonSerializerOptions _serializerOptions`
- L107 _private* field_ `readonly ILogger _logger`
- L114-119 _public ctor_ `public SlackClient(HttpClient httpClient, ILogger logger)` — Constructor
- L122-125 _public method_ `public void Dispose()` — (inheritdoc)
- L133-161 _public method_ `public static SlackClient Create(string? slackToken, ILogger logger)` — attrs: `[SuppressMessage("Reliability", "CA2000:Dispose objects before losing scope", Justification = "Polly handler is disposed by HttpClient")]` — Create a Slack client with a retry policy
- L163-178 _private* method_ `static SlackErrorBehavior GetErrorBehavior<TResponse>(TResponse response) where TResponse : SlackResponse`
- L180-183 _private method_ `private Task<TResponse> SendRequestAsync<TResponse>(string requestUrl, object request, CancellationToken cancellationToken) where TResponse : SlackResponse`
- L185-192 _private method_ `private async Task<TResponse> SendRequestAsync<TResponse>(string requestUrl, object request, Func<TResponse, SlackErrorBehavior> getErrorBehavior, CancellationToken cancellationToken) where TResponse : SlackResponse`
- L194-197 _private method_ `private Task<TResponse> SendRequestAsync<TResponse>(HttpRequestMessage request, string requestJson, CancellationToken cancellationToken) where TResponse : SlackResponse`
- L199-224 _private method_ `private async Task<TResponse> SendRequestAsync<TResponse>(HttpRequestMessage request, string requestJson, Func<TResponse, SlackErrorBehavior> getErrorBehavior, CancellationToken cancellationToken) where TResponse : SlackResponse`
- L228 _private* const_ `const string PostMessageUrl = "https://slack.com/api/chat.postMessage"`
- L229 _private* const_ `const string UpdateMessageUrl = "https://slack.com/api/chat.update"`
- L230 _private* const_ `const string GetPermalinkUrl = "https://slack.com/api/chat.getPermalink"`
- L281-284 _public method_ `public async Task<SlackMessageId> PostMessageAsync(string recipient, SlackMessage message, CancellationToken cancellationToken = default)` — Posts a message to a recipient
- L293-296 _public method_ `public Task<SlackMessageId> PostMessageToThreadAsync(SlackMessageId threadId, SlackMessage message, CancellationToken cancellationToken = default)` — Posts a message to a recipient
- L306-309 _public method_ `public async Task<SlackMessageId> PostMessageToThreadAsync(SlackMessageId threadId, SlackMessage message, bool replyBroadcast, CancellationToken cancellationToken = default)` — Posts a message to a recipient
- L317-320 _public method_ `public Task UpdateMessageAsync(SlackMessageId id, SlackMessage message, CancellationToken cancellationToken = default)` — Updates an existing message
- L329-332 _public method_ `public async Task UpdateMessageAsync(SlackMessageId id, SlackMessage message, bool replyBroadcast = false, CancellationToken cancellationToken = default)` — Updates an existing message
- L334-368 _private* method_ `async Task<SlackMessageId> PostOrUpdateMessageAsync(string recipient, string? ts, string? threadTs, SlackMessage message, bool replyBroadcast, CancellationToken cancellationToken)`
- L394-406 _public method_ `public async Task<string> GetPermalinkAsync(SlackMessageId id, CancellationToken cancellationToken = default)` — Gets a permalink for a message
- L412 _private* const_ `const string AddReactionUrl = "https://slack.com/api/reactions.add"`
- L413 _private* const_ `const string RemoveReactionUrl = "https://slack.com/api/reactions.remove"`
- L427-435 _private* method_ `static SlackErrorBehavior GetReactionErrorBehavior<TResponse>(TResponse response) where TResponse : SlackResponse`
- L443-451 _public method_ `public async Task AddReactionAsync(SlackMessageId messageId, string name, CancellationToken cancellationToken = default)` — Adds a reaction to a posted message
- L459-467 _public method_ `public async Task RemoveReactionAsync(SlackMessageId messageId, string name, CancellationToken cancellationToken = default)` — Removes a reaction from a posted message
- L473 _private* const_ `const string ConversationsInviteUrl = "https://slack.com/api/conversations.invite"`
- L474 _private* const_ `const string ConversationsOpenUrl = "https://slack.com/api/conversations.open"`
- L509 _public method_ `public Task InviteUserAsync(string channel, string userId, CancellationToken cancellationToken = default)` — Invite a user to a channel
- L517-524 _public method_ `public async Task InviteUsersAsync(string channel, IEnumerable<string> userIds, CancellationToken cancellationToken = default)` — Invite a set of users to a channel
- L532-541 _public method_ `public async Task<string?> TryInviteUsersAsync(string channel, IEnumerable<string> userIds, CancellationToken cancellationToken = default)` — Attempt to invite a set of users to a channel, returning the error code on failure
- L543 _private* const_ `const string AdminConversationsInviteUrl = "https://slack.com/api/admin.conversations.invite"`
- L551-556 _public method_ `public async Task AdminInviteUsersAsync(string channel, IEnumerable<string> userIds, CancellationToken cancellationToken = default)` — Invite a set of users to a channel using admin powers.
- L564-576 _public method_ `public async Task <string?> OpenDirectMessageAsync(IEnumerable<string> userIds, CancellationToken cancellationToken = default)` — Open a direct message with multiple users
- L582 _private* const_ `const string UsersInfoUrl = "https://slack.com/api/users.info"`
- L583 _private* const_ `const string UsersLookupByEmailUrl = "https://slack.com/api/users.lookupByEmail"`
- L597-606 _public method_ `public async Task<SlackUser> GetUserAsync(string userId, CancellationToken cancellationToken = default)` — Gets a user's profile
- L614-627 _public method_ `public async Task<SlackUser?> FindUserByEmailAsync(string email, CancellationToken cancellationToken = default)` — Finds a user by email address
- L633 _private* const_ `const string ViewsOpenUrl = "https://slack.com/api/views.open"`
- L650-656 _public method_ `public async Task OpenViewAsync(string triggerId, SlackView view, CancellationToken cancellationToken = default)` — Open a new modal view, in response to a trigger

#### class `EpicGames.Slack.SlackClient.SlackResponse`  
`class SlackResponse`  
_private*; L96-103_
- L99 _public property_ `public bool Ok { get; set; }` — attrs: `[JsonPropertyName("ok")]`
- L102 _public property_ `public string? Error { get; set; }` — attrs: `[JsonPropertyName("error")]`

#### class `EpicGames.Slack.SlackClient.PostMessageRequest`  
`class PostMessageRequest`  
_private*; L232-263_
- L235 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L238 _public property_ `public string? Ts { get; set; }` — attrs: `[JsonPropertyName("ts")]`
- L241 _public property_ `public string? ThreadTs { get; set; }` — attrs: `[JsonPropertyName("thread_ts")]`
- L244 _public property_ `public string? Text { get; set; }` — attrs: `[JsonPropertyName("text")]`
- L247 _public property_ `public bool? Markdown { get; set; }` — attrs: `[JsonPropertyName("mrkdwn")]`
- L250 _public property_ `public List<Block>? Blocks { get; set; }` — attrs: `[JsonPropertyName("blocks")]`
- L253 _public property_ `public List<SlackAttachment>? Attachments { get; set; }` — attrs: `[JsonPropertyName("attachments")]`
- L256 _public property_ `public bool? ReplyBroadcast { get; set; }` — attrs: `[JsonPropertyName("reply_broadcast")]`
- L259 _public property_ `public bool? UnfurlLinks { get; set; }` — attrs: `[JsonPropertyName("unfurl_links")]`
- L262 _public property_ `public bool? UnfurlMedia { get; set; }` — attrs: `[JsonPropertyName("unfurl_media")]`

#### class `EpicGames.Slack.SlackClient.PostMessageResponse`  
`class PostMessageResponse : SlackResponse`  
_private*; L265-272_
- inherits: `SlackResponse`
- L268 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L271 _public property_ `public string? Ts { get; set; }` — attrs: `[JsonPropertyName("ts")]`

#### class `EpicGames.Slack.SlackClient.GetPermalinkRequest`  
`class GetPermalinkRequest`  
_private*; L370-377_
- L373 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L376 _public property_ `public string? MessageTs { get; set; }` — attrs: `[JsonPropertyName("message_ts")]`

#### class `EpicGames.Slack.SlackClient.GetPermalinkResponse`  
`class GetPermalinkResponse : SlackResponse`  
_private*; L379-386_
- inherits: `SlackResponse`
- L382 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L385 _public property_ `public string? Permalink { get; set; }` — attrs: `[JsonPropertyName("permalink")]`

#### class `EpicGames.Slack.SlackClient.ReactionMessage`  
`class ReactionMessage`  
_private*; L415-425_
- L418 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L421 _public property_ `public string? Ts { get; set; }` — attrs: `[JsonPropertyName("timestamp")]`
- L424 _public property_ `public string? Name { get; set; }` — attrs: `[JsonPropertyName("name")]`

#### class `EpicGames.Slack.SlackClient.InviteMessage`  
`class InviteMessage`  
_private*; L476-483_
- L479 _public property_ `public string? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`
- L482 _public property_ `public string? Users { get; set; }` — attrs: `[JsonPropertyName("users")]`

#### class `EpicGames.Slack.SlackClient.OpenDirectMessage`  
`class OpenDirectMessage`  
_private*; L485-489_
- L488 _public property_ `public string? Users { get; set; }` — attrs: `[JsonPropertyName("users")]`

#### class `EpicGames.Slack.SlackClient.GetChannelResponse`  
`class GetChannelResponse : SlackResponse`  
_private*; L491-495_
- inherits: `SlackResponse`
- L494 _public property_ `public SlackChannelObject? Channel { get; set; }` — attrs: `[JsonPropertyName("channel")]`

#### class `EpicGames.Slack.SlackClient.SlackChannelObject`  
`class SlackChannelObject`  
_private*; L497-501_
- L500 _public property_ `public string Id { get; set; }` — attrs: `[JsonPropertyName("id")]`

#### class `EpicGames.Slack.SlackClient.UserResponse`  
`class UserResponse : SlackResponse`  
_private*; L585-589_
- inherits: `SlackResponse`
- L588 _public property_ `public SlackUser? User { get; set; }` — attrs: `[JsonPropertyName("user")]`

#### class `EpicGames.Slack.SlackClient.ViewsOpenRequest`  
`class ViewsOpenRequest`  
_private*; L635-642_
- L638 _public property_ `public string? TriggerId { get; set; }` — attrs: `[JsonPropertyName("trigger_id")]`
- L641 _public property_ `public SlackView? View { get; set; }` — attrs: `[JsonPropertyName("view")]`

### `Source/Programs/Shared/EpicGames.Slack/SlackConfirm.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackConfirm`  
`public class SlackConfirm`  
_public; L11-70_
- desc: An object that defines a dialog that provides a confirmation step to any interactive element. This dialog will ask the user to confirm their action by offering a confirm and deny buttons.
- L17 _public property_ `public PlainTextObject Title { get; set; }` — attrs: `[JsonPropertyName("title")]` — A plain_text-only text object that defines the dialog's title. Maximum length for this field is 100 characters.
- L23 _public property_ `public TextObject Text { get; set; }` — attrs: `[JsonPropertyName("text")]` — A text object that defines the explanatory text that appears in the confirm dialog. Maximum length for the text in this field is 300 characters.
- L29 _public property_ `public PlainTextObject Confirm { get; set; }` — attrs: `[JsonPropertyName("confirm")]` — A plain_text-only text object to define the text of the button that confirms the action. Maximum length for the text in this field is 30 characters.
- L35 _public property_ `public PlainTextObject Deny { get; set; }` — attrs: `[JsonPropertyName("deny")]` — A plain_text-only text object to define the text of the button that cancels the action. Maximum length for the text in this field is 30 characters.
- L41 _public property_ `public ButtonStyle Style { get; set; }` — attrs: `[JsonPropertyName("style")]` — Defines the color scheme applied to the confirm button. A value of danger will display the button with a red background on desktop, or red text on mobile. A value of primary will display the button with a green background on desktop, or blue text on mobile. If this field is not provided, the default value will be primary.
- L46-49 _public ctor_ `public SlackConfirm(string title, string text, string confirm, string deny, ButtonStyle style = ButtonStyle.Primary) : this(title, new PlainTextObject(text), confirm, deny, style)` — Constructor
- L54-57 _public ctor_ `public SlackConfirm(string title, TextObject text, string confirm, string deny, ButtonStyle style = ButtonStyle.Primary) : this(new PlainTextObject(title), text, new PlainTextObject(confirm), new PlainTextObject(deny), style)` — Constructor
- L62-69 _public ctor_ `public SlackConfirm(PlainTextObject title, TextObject text, PlainTextObject confirm, PlainTextObject deny, ButtonStyle style = ButtonStyle.Primary)` — Constructor

### `Source/Programs/Shared/EpicGames.Slack/SlackMessage.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackMessage`  
`public class SlackMessage : ISlackBlockContainer`  
_public; L10-52_
- inherits: `ISlackBlockContainer`
- desc: A slack message object
- L15 _public property_ `public string? Text { get; set; }` — The formatted text of the message to be published. If blocks are included, this will become the fallback text used in notifications.
- L20 _public property_ `public bool? Markdown { get; set; }` — Disable Slack markup parsing by setting to false. Enabled by default.
- L25 _public property_ `public List<Block> Blocks { get; }` — A JSON-based array of structured blocks, presented as a URL-encoded string.
- L30 _public property_ `public List<SlackAttachment> Attachments { get; }` — Attachments for the message
- L35 _public property_ `public bool UnfurlLinks { get; set; }` — Pass true to enable unfurling of primarily text-based content.
- L40 _public property_ `public bool UnfurlMedia { get; set; }` — Pass false to disable unfurling of media content.
- L46-51 _public operator_ `public static implicit operator SlackMessage(string text)` — Implciit conversion operator from a Markdown string

### `Source/Programs/Shared/EpicGames.Slack/SlackOption.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackOption`  
`public class SlackOption`  
_public; L13-64_
- desc: An object that represents a single selectable item in a select menu, multi-select menu, checkbox group, radio button group, or overflow menu.
- L20 _public property_ `public TextObject Text { get; set; }` — attrs: `[JsonPropertyName("text")]` — A text object that defines the text shown in the option on the menu. Overflow, select, and multi-select menus can only use plain_text objects, while radio buttons and checkboxes can use mrkdwn text objects. Maximum length for the text in this field is 75 characters.
- L26 _public property_ `public string Value { get; set; }` — attrs: `[JsonPropertyName("value")]` — A unique string value that will be passed to your app when this option is chosen. Maximum length for this field is 75 characters.
- L32 _public property_ `public PlainTextObject? Description { get; set; }` — attrs: `[JsonPropertyName("description")]` — A plain_text only text object that defines a line of descriptive text shown below the text field beside the radio button. Maximum length for the text object within this field is 75 characters.
- L38 _public property_ `public Uri? Url { get; set; }` — attrs: `[JsonPropertyName("url")]` — A URL to load in the user's browser when the option is clicked. The url attribute is only available in overflow menus. Maximum length for this field is 3000 characters. If you're using url, you'll still receive an interaction payload and will need to send an acknowledgement response.
- L43-46 _public ctor_ `public SlackOption() : this("", "")` — Constructor
- L51-55 _public ctor_ `public SlackOption(TextObject text, string value)` — Constructor
- L60-63 _public ctor_ `public SlackOption(string text, string value) : this(new PlainTextObject(text), value)` — Constructor

#### class `EpicGames.Slack.SlackOptionGroup`  
`public class SlackOptionGroup`  
_public; L69-89_
- desc: Provides a way to group options in a select menu or multi-select menu.
- L74 _public property_ `public PlainTextObject Label { get; }` — A plain_text only text object that defines the label shown above this group of options. Maximum length for the text in this field is 75 characters.
- L79 _public property_ `public List<SlackOption> Options { get; }` — An array of option objects that belong to this specific group. Maximum of 100 items.
- L84-88 _public ctor_ `public SlackOptionGroup(PlainTextObject label, List<SlackOption> options)` — Constructor

### `Source/Programs/Shared/EpicGames.Slack/SlackUser.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackUser`  
`public class SlackUser`  
_public; L10-41_
- desc: Information about a Slack user
- L16 _public property_ `public string? Id { get; set; }` — attrs: `[JsonPropertyName("id")]` — Identifier for this workspace user. It is unique to the workspace containing the user. Use this field together with team_id as a unique key when storing related data or when specifying the user in API requests. We recommend considering the format of the string to be an opaque value, and not to rely on a particular structure.
- L22 _public property_ `public SlackUserProfile? Profile { get; set; }` — attrs: `[JsonPropertyName("profile")]` — The profile object contains the default fields of a user's workspace profile. A user's custom profile fields may be discovered using users.profile.get.
- L28 _public property_ `public string? Timezone { get; set; }` — attrs: `[JsonPropertyName("tz")]` — A human-readable string for the geographic timezone-related region this user has specified in their account.
- L34 _public property_ `public string? TimezoneLabel { get; set; }` — attrs: `[JsonPropertyName("tz_label")]` — Describes the commonly used name of the tz timezone.
- L40 _public property_ `public int TimezoneOffset { get; set; }` — attrs: `[JsonPropertyName("tz_offset")]` — Indicates the number of seconds to offset UTC time by for this user's tz.

#### class `EpicGames.Slack.SlackUserProfile`  
`public class SlackUserProfile`  
_public; L46-101_
- desc: Profile information for a Slack user
- L52 _public property_ `public string DisplayName { get; set; }` — attrs: `[JsonPropertyName("display_name")]` — The display name the user has chosen to identify themselves by in their workspace profile. Do not use this field as a unique identifier for a user, as it may change at any time. Instead, use id and team_id in concert.
- L58 _public property_ `public string Email { get; set; }` — attrs: `[JsonPropertyName("email")]` — A valid email address. It cannot have spaces, and it must have an @ and a domain. It cannot be in use by another member of the same team. Changing a user's email address will send an email to both the old and new addresses, and also post a slackbot to the user informing them of the change. This field can only be changed by admins for users on paid teams.
- L64 _public property_ `public string FirstName { get; set; }` — attrs: `[JsonPropertyName("first_name")]` — The user's first name. The name slackbot cannot be used. Updating first_name will update the first name within real_name.
- L70 _public property_ `public string LastName { get; set; }` — attrs: `[JsonPropertyName("last_name")]` — The user's last name. The name slackbot cannot be used. Updating last_name will update the second name within real_name.
- L76 _public property_ `public string RealName { get; set; }` — attrs: `[JsonPropertyName("real_name")]` — The user's first and last name. Updating this field will update first_name and last_name. If only one name is provided, the value of last_name will be cleared.
- L82 _public property_ `public bool IsCustomImage { get; set; }` — attrs: `[JsonPropertyName("is_custom_image")]` — Whether the user has a custom profile image
- L88 _public property_ `public string? Image24 { get; set; }` — attrs: `[JsonPropertyName("image_24")]` — These various fields will contain https URLs that point to square ratio, web-viewable images (GIFs, JPEGs, or PNGs) that represent different sizes of a user's profile picture.
- L92 _public property_ `public string? Image32 { get; set; }` — attrs: `[JsonPropertyName("image_32")]` — (inheritdoc)
- L96 _public property_ `public string? Image48 { get; set; }` — attrs: `[JsonPropertyName("image_48")]` — (inheritdoc)
- L100 _public property_ `public string? Image72 { get; set; }` — attrs: `[JsonPropertyName("image_72")]` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Slack/SlackView.cs` (EpicGames.Slack)


#### class `EpicGames.Slack.SlackView`  
`public class SlackView : ISlackBlockContainer`  
_public; L14-96_
- inherits: `ISlackBlockContainer`
- desc: Describes a Slack view
- L20 _public property_ `public string Type { get; }` — attrs: `[JsonPropertyName("type")]` — The type of view. Set to modal for modals and home for Home tabs.
- L26 _public property_ `public PlainTextObject Title { get; set; }` — attrs: `[JsonPropertyName("title")]` — The title that appears in the top-left of the modal. Must be a plain_text text element with a max length of 24 characters.
- L32 _public property_ `public List<Block> Blocks { get; }` — attrs: `[JsonPropertyName("blocks")]` — An array of blocks that defines the content of the view. Max of 100 blocks.
- L38 _public property_ `public PlainTextObject? Close { get; set; }` — attrs: `[JsonPropertyName("close")]` — An optional plain_text element that defines the text displayed in the close button at the bottom-right of the view. Max length of 24 characters.
- L44 _public property_ `public PlainTextObject? Submit { get; set; }` — attrs: `[JsonPropertyName("submit")]` — An optional plain_text element that defines the text displayed in the submit button at the bottom-right of the view. submit is required when an input block is within the blocks array. Max length of 24 characters.
- L50 _public property_ `public string? PrivateMetadata { get; set; }` — attrs: `[JsonPropertyName("private_metadata")]` — An optional string that will be sent to your app in view_submission and block_actions events. Max length of 3000 characters.
- L56 _public property_ `public string? CallbackId { get; set; }` — attrs: `[JsonPropertyName("callback_id")]` — An identifier to recognize interactions and submissions of this particular view.Don't use this to store sensitive information (use private_metadata instead). Max length of 255 characters.
- L62 _public property_ `public bool? ClearOnClose { get; set; }` — attrs: `[JsonPropertyName("clear_on_close")]` — When set to true, clicking on the close button will clear all views in a modal and close it. Defaults to false.
- L68 _public property_ `public bool? NotifyOnClose { get; set; }` — attrs: `[JsonPropertyName("notify_on_close")]` — Indicates whether Slack will send your request URL a view_closed event when a user clicks the close button. Defaults to false.
- L74 _public property_ `public string? ExternalId { get; set; }` — attrs: `[JsonPropertyName("external_id")]` — A custom identifier that must be unique for all views on a per-team basis.
- L80 _public property_ `public bool? SubmitDisabled { get; set; }` — attrs: `[JsonPropertyName("submit_disabled")]` — When set to true, disables the submit button until the user has completed one or more inputs. This property is for configuration modals.
- L86 _public property_ `public SlackViewState? State { get; set; }` — attrs: `[JsonPropertyName("state")]` — State value when returned via a form notification
- L92-95 _public ctor_ `public SlackView(PlainTextObject title)` — Constructor

#### class `EpicGames.Slack.SlackViewState`  
`public class SlackViewState`  
_public; L101-146_
- desc: State object returned from a submission
- L108 _public property_ `public Dictionary<string, Dictionary<string, SlackViewValue>> Values { get; set; }` — attrs: `[JsonPropertyName("values")]` — Values for the form, by blockId, then by actionId
- L114-127 _public method_ `public bool TryGetValue(string blockId, string actionId, [NotNullWhen(true)] out string? value)` — Gets a value from the state
- L132-145 _public method_ `public bool TryGetValue(string blockId, string actionId, [NotNullWhen(true)] out SlackViewValue? value)` — Gets a value from the state

#### class `EpicGames.Slack.SlackViewValue`  
`public class SlackViewValue`  
_public; L151-170_
- desc: Value for a form item
- L157 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("type")]` — The item type
- L163 _public property_ `public string? Value { get; set; }` — attrs: `[JsonPropertyName("value")]` — Value for the widget (used for text fields)
- L169 _public property_ `public SlackOption? SelectedOption { get; set; }` — attrs: `[JsonPropertyName("selected_option")]` — Current selected option (used for radio buttons)
